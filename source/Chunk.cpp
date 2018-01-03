#include "Chunk.h"
#include "WorldGen.h"
#include "World.h"
#include "Blocks.h"
#include <algorithm>
#include <fstream>

namespace ChunkRenderer {
	void RenderChunk(World::Chunk* c);
	void MergeFaceRender(World::Chunk* c);
	void RenderDepthModel(World::Chunk* c);
}

namespace Renderer {
	extern bool AdvancedRender;
}

namespace World {

    struct HMapManager {
        int H[16][16];
        int low, high, count;
        HMapManager() {};
        HMapManager(int cx, int cz) {
            int l = MAXINT, hi = WorldGen::WaterLevel, h;
            for (int x = 0; x < 16; ++x) {
                for (int z = 0; z < 16; ++z) {
                    h = HMap.getHeight(cx * 16 + x, cz * 16 + z);
                    if (h < l) l = h;
                    if (h > hi) hi = h;
                    H[x][z] = h;
                }
            }
            low = (l - 21) / 16, high = (hi + 16) / 16; count = 0;
        }
    };

    double Chunk::relBaseX, Chunk::relBaseY, Chunk::relBaseZ;
    Frustum Chunk::TestFrustum;

    Chunk::Chunk(int cxi, int cyi, int czi, ChunkID idi) : cx(cxi), cy(cyi), cz(czi), id(idi),
        mIsModified(false), mIsEmpty(false), mIsUpdated(false), mIsRenderBuilt(false), mIsDetailGenerated(false), loadAnim(0.0), vertexes{ 0 }, vbuffer{ 0 } {
        mAABB = getBaseAABB();
    }

    Chunk::~Chunk()
    {
        unloadedChunksCount++;
        SaveToFile();
        destroyRender();
        mIsUpdated = false;
        unloadedChunks++;
    }

	void Chunk::buildTerrain(bool initIfEmpty) {
		//Fast generate parts
		//Part1 out of the terrain bound
		if (cy > 4) {
			mIsEmpty = true;
			if (!initIfEmpty) return;
			memset(mBlocks, 0, 4096 * sizeof(Block));
			for (int i = 0; i < 4096; i++) mBrightness[i] = skylight;
			return;
		}
		if (cy < 0) {
			mIsEmpty = true;
			if (!initIfEmpty) return;
			memset(mBlocks, 0, 4096 * sizeof(Block));
			for (int i = 0; i < 4096; i++) mBrightness[i] = BrightnessMin;
			return;
		}

		//Part2 out of geomentry area
		HMapManager cur = HMapManager(cx, cz);
		if (cy > cur.high) {
			mIsEmpty = true;
			if (!initIfEmpty) return;
			memset(mBlocks, 0, 4096 * sizeof(Block));
			for (int i = 0; i < 4096; i++) mBrightness[i] = skylight;
			return;
		}
		if (cy < cur.low) {
			for (int i = 0; i < 4096; i++) mBlocks[i] = Blocks::ROCK;
			memset(mBrightness, 0, 4096 * sizeof(Brightness));
			if (cy == 0) for (int x = 0; x < 16; x++) for (int z = 0; z < 16; z++) mBlocks[x * 256 + z] = Blocks::BEDROCK;
			mIsEmpty = false; return;
		}

		//Normal Calc
		//Init
		memset(mBlocks, 0, 4096 * sizeof(Block)); //mIsEmpty the chunk
		memset(mBrightness, 0, 4096 * sizeof(Brightness)); //Set All Brightness to 0

		int x, z, h = 0, sh = 0, wh = 0;
		int minh, maxh, cur_br;

		mIsEmpty = true;
		sh = WorldGen::WaterLevel + 2 - (cy << 4);
		wh = WorldGen::WaterLevel - (cy << 4);

		for (x = 0; x < 16; ++x) {
			for (z = 0; z < 16; ++z) {
				int base = (x << 8) + z;
				h = cur.H[x][z] - (cy << 4);
				if (h >= 0 || wh >= 0) mIsEmpty = false;
				if (h > sh && h > wh + 1) {
					//Grass layer
					if (h >= 0 && h < 16) mBlocks[(h << 4) + base] = Blocks::GRASS;
					//Dirt layer
					maxh = std::min(std::max(0, h), 16);
					for (int y = std::min(std::max(0, h - 5), 16); y < maxh; ++y) mBlocks[(y << 4) + base] = Blocks::DIRT;
				}
				else {
					//Sand layer
					maxh = std::min(std::max(0, h + 1), 16);
					for (int y = std::min(std::max(0, h - 5), 16); y < maxh; ++y) mBlocks[(y << 4) + base] = Blocks::SAND;
					//Water layer
					minh = std::min(std::max(0, h + 1), 16); maxh = std::min(std::max(0, wh + 1), 16);
					cur_br = BrightnessMax - (WorldGen::WaterLevel - (maxh - 1 + (cy << 4))) * 2;
					if (cur_br < BrightnessMin) cur_br = BrightnessMin;
					for (int y = maxh - 1; y >= minh; --y) {
						mBlocks[(y << 4) + base] = Blocks::WATER;
						mBrightness[(y << 4) + base] = (Brightness)cur_br;
						cur_br -= 2; if (cur_br < BrightnessMin) cur_br = BrightnessMin;
					}
				}
				//Rock layer
				maxh = std::min(std::max(0, h - 5), 16);
				for (int y = 0; y < maxh; ++y) mBlocks[(y << 4) + base] = Blocks::ROCK;
				//Air layer
				for (int y = std::min(std::max(0, std::max(h + 1, wh + 1)), 16); y < 16; ++y) {
					mBlocks[(y << 4) + base] = Blocks::AIR;
					mBrightness[(y << 4) + base] = skylight;
				}
				//Bedrock layer (overwrite)
				if (cy == 0) mBlocks[base] = Blocks::BEDROCK;
			}
		}
	}

	void Chunk::buildDetail() {
		int index = 0;
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				for (int z = 0; z < 16; z++) {
					//Tree
					if (mBlocks[index] == Blocks::GRASS && rnd() < 0.005) {
						buildtree(cx * 16 + x, cy * 16 + y, cz * 16 + z);
					}
					index++;
				}
			}
		}
	}

	void Chunk::build(bool initIfEmpty) {
		buildTerrain(initIfEmpty);
		if (!mIsEmpty) 
            buildDetail();
        mIsModified = false;
	}

	void Chunk::load(bool initIfEmpty) {
		if (!LoadFromFile()) 
            build(initIfEmpty);
		if (!mIsEmpty) 
            mIsUpdated = true;
	}

	bool Chunk::LoadFromFile() {
		std::ifstream file(getChunkPath(), std::ios::in | std::ios::binary);
		bool openChunkFile = file.is_open();
		file.read((char*)mBlocks, 4096 * sizeof(Block));
		file.read((char*)mBrightness, 4096 * sizeof(Brightness));
		file.read((char*)&mIsDetailGenerated, sizeof(bool));
        file.close();
		return openChunkFile;
	}

	void Chunk::SaveToFile(){
		if (!mIsEmpty&&mIsModified) {
			std::ofstream file(getChunkPath(), std::ios::out | std::ios::binary);
			file.write((char*)mBlocks, 4096 * sizeof(Block));
			file.write((char*)mBrightness, 4096 * sizeof(Brightness));
			file.write((char*)&mIsDetailGenerated, sizeof(bool));
			file.close();
		}
		if (objects.size() != 0) {

		}
	}

    void Chunk::buildRender() {
        for (int8_t x = -1; x <= 1; x++)
            for (int8_t y = -1; y <= 1; y++)
                for (int8_t z = -1; z <= 1; z++)
                    if (x && y && z)
                        if (!chunkLoaded(cx + x, cy + y, cz + z))
                            return;
		
		rebuiltChunks++;
		updatedChunks++;

		if (!mIsRenderBuilt) {
			mIsRenderBuilt = true;
			loadAnim = cy * 16.0f + 16.0f;
		}
		
		if (MergeFace) 
            ChunkRenderer::MergeFaceRender(this);
		else 
            ChunkRenderer::RenderChunk(this);
		if (Renderer::AdvancedRender) 
            ChunkRenderer::RenderDepthModel(this);

		mIsUpdated = false;
	}

	void Chunk::destroyRender() {
		if (!mIsRenderBuilt) return;
		if (vbuffer[0] != 0) vbuffersShouldDelete.push_back(vbuffer[0]);
		if (vbuffer[1] != 0) vbuffersShouldDelete.push_back(vbuffer[1]);
		if (vbuffer[2] != 0) vbuffersShouldDelete.push_back(vbuffer[2]);
		if (vbuffer[3] != 0) vbuffersShouldDelete.push_back(vbuffer[3]);
		vbuffer[0] = vbuffer[1] = vbuffer[2] = vbuffer[3] = 0;
		mIsRenderBuilt = false;
	}

	Hitbox::AABB Chunk::getBaseAABB(){
		Hitbox::AABB ret;
		ret.xmin = cx * 16 - 0.5;
		ret.ymin = cy * 16 - 0.5;
		ret.zmin = cz * 16 - 0.5;
		ret.xmax = cx * 16 + 16 - 0.5;
		ret.ymax = cy * 16 + 16 - 0.5;
		ret.zmax = cz * 16 + 16 - 0.5;
		return ret;
	}

	Frustum::ChunkBox Chunk::getRelativeAABB() {
		Frustum::ChunkBox ret;
		ret.xmin = (float)(mAABB.xmin - relBaseX);
		ret.xmax = (float)(mAABB.xmax - relBaseX);
		ret.ymin = (float)(mAABB.ymin - loadAnim - relBaseY);
		ret.ymax = (float)(mAABB.ymax - loadAnim - relBaseY);
		ret.zmin = (float)(mAABB.zmin - relBaseZ);
		ret.zmax = (float)(mAABB.zmax - relBaseZ);
		return ret;
	}
	
}
