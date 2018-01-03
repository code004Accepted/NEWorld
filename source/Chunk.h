#pragma once
#include "Definitions.h"
#include "Hitbox.h"
#include "Blocks.h"
#include "Frustum.h"

class Object;

namespace World {
	extern std::string worldname;
	extern Brightness skylight;

	class Chunk;

    // This function will only be used on client side, so just checking the lower 20 bits will be enough
    constexpr ChunkID getChunkID(int x, int y, int z) noexcept {
        return (ChunkID(x & 0xFFFFF) << 40) + (ChunkID(y & 0xFFFFF) << 20) + (z & 0xFFFFF);
    }

	void explode(int x, int y, int z, int r, Chunk* c);

	class Chunk{
	public:
		//竟然一直都没有构造函数/析构函数 还要手动调用Init...我受不了啦(╯‵□′)╯︵┻━┻ --Null
		//2333 --qiaozhanrong
        Chunk(int cxi, int cyi, int czi, ChunkID idi);
        ~Chunk();
		int cx, cy, cz;
		bool mIsEmpty, mIsUpdated, mIsRenderBuilt, mIsModified, mIsDetailGenerated;
		ChunkID id;
		vtxCount vertexes[4];
		VBOID vbuffer[4];
		double loadAnim;
		bool visible;

		void load(bool initIfEmpty = true);
		void buildRender();
		inline Block getBlock(int x, int y, int z) {
			return mBlocks[(x << 8) ^ (y << 4) ^ z];
		}
		inline Brightness getBrightness(int x, int y, int z){
			return mBrightness[(x << 8) ^ (y << 4) ^ z];
		}
		inline void setblock(int x, int y, int z, Block iblock) {
			if (iblock == Blocks::TNT) {
				World::explode(cx * 16 + x, cy * 16 + y, cz * 16 + z, 8, this);
				return;
			}
			mBlocks[(x << 8) ^ (y << 4) ^ z] = iblock;
			mIsModified = true;
		}
		inline void setbrightness(int x, int y, int z, Brightness ibrightness){
			mBrightness[(x << 8) ^ (y << 4) ^ z] = ibrightness;
			mIsModified = true;
		}

		static void setRelativeBase(double x, double y, double z, Frustum& frus) {
			relBaseX = x; relBaseY = y; relBaseZ = z; TestFrustum = frus;
		}

		Frustum::ChunkBox getRelativeAABB();
		inline void calcVisible() { visible = TestFrustum.FrustumTest(getRelativeAABB()); }
    private:
        Block mBlocks[4096];
        Brightness mBrightness[4096];
        std::vector<Object*> objects;
        Hitbox::AABB mAABB;
        static double relBaseX, relBaseY, relBaseZ;
        static Frustum TestFrustum;
        bool LoadFromFile(); //返回true代表区块文件打开成功
        void SaveToFile();
        void destroyRender();
        Hitbox::AABB getBaseAABB();
        void buildTerrain(bool initIfEmpty = true);
        void buildDetail();
        void build(bool initIfEmpty = true);
        inline std::string getChunkPath() {
            std::stringstream ss;
            ss << "Worlds/" << worldname << "/chunks/chunk_" << cx << "_" << cy << "_" << cz;
            return ss.str();
        }
	};
}
