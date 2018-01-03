#pragma once
#include "Definitions.h"
#include "chunkPtrArray.h"
#include "HeightMap.h"
#include "Chunk.h"
#include "Hitbox.h"
#include "Blocks.h"
#include "Player.h"
#include "Particles.h"
#include "Items.h"

extern int viewdistance;
class Frsutum;

namespace World {

    // POD ONLY!
    template <class Tk, class Td, size_t size, template<class> class Compare = std::less>
    class OrderedList
    {
    public:
        OrderedList() noexcept : mComp(), mSize(0) {}
        using ArrayType = std::array<std::pair<Tk, Td>, size>;
        using Iterator = typename ArrayType::iterator;
        using ConstIterator = typename ArrayType::const_iterator;
        Iterator begin() noexcept { return mList.begin(); }
        ConstIterator begin() const noexcept { return mList.begin(); }
        Iterator end() noexcept { return mList.begin() + mSize; }
        ConstIterator end() const noexcept { return mList.begin() + mSize; }
        void insert(Tk key, Td data) noexcept
        {
            int first = 0, last = mSize - 1;
            while (first <= last)
            {
                int middle = (first + last) / 2;
                if (mComp(key, mList[middle].first))
                    last = middle - 1;
                else
                    first = middle + 1;
            }
            if (first <= mSize && first < size)
            {
                mSize = std::min(size, mSize + 1);
                for (int j = size - 1; j > first; j--)
                    mList[j] = mList[j - 1];
                mList[first] = std::pair<Tk, Td>(key, data);
            }
        }
        void clear() noexcept { mSize = 0; }
    private:
        size_t mSize;
        ArrayType mList;
        Compare<Tk> mComp;
    };

	extern std::string worldname;
	const int worldsize = 134217728;
	const int worldheight = 128;
    constexpr Brightness BrightnessMax = 15;    //maximum brightness
    constexpr Brightness BrightnessMin = 2;     //Mimimum brightness
    constexpr Brightness BrightnessDec = 1;     //Brightness decrease
    extern Brightness skylight;         //Sky light level
	extern Chunk* EmptyChunkPtr;
	extern unsigned int EmptyBuffer;
	extern int maxChunkLoads;
	extern int maxChunkUnloads;
	extern int maxChunkRenders;

	extern Chunk** chunks;
	extern int loadedChunks, chunkArraySize;
	extern Chunk* cpCachePtr;
	extern ChunkID cpCacheID;
	extern HeightMap HMap;
	extern CPARegionalCache cpArray;

	extern int cloud[128][128];
	extern int rebuiltChunks, rebuiltChunksCount;
	extern int updatedChunks, updatedChunksCount;
	extern int unloadedChunks, unloadedChunksCount;
	extern int chunkBuildRenderList[256][2];
	extern int chunkLoadList[256][4];
	extern std::pair<Chunk*, int> chunkUnloadList[256];
	extern std::vector<unsigned int> vbuffersShouldDelete;
	extern int chunkBuildRenders, chunkLoads, chunkUnloads;

	void Init();

	Chunk* AddChunk(int x, int y, int z);
	void DeleteChunk(int x, int y, int z);

	Chunk* getChunkPtr(int x, int y, int z);
    template <class T> constexpr auto getChunkPos(T n) noexcept { return n >> 4; }
    template <class T> constexpr auto getBlockPos(T n) noexcept { return n & 0xF; }

	inline bool chunkLoaded(int x, int y, int z) {
        return getChunkPtr(x, y, z);
	}

    std::vector<Hitbox::AABB> getHitboxes(const Hitbox::AABB& box);
	bool inWater(const Hitbox::AABB& box);

	void renderblock(int x, int y, int z, Chunk* chunkptr);
	void updateblock(int x, int y, int z, bool blockchanged, int depth = 0);
	Block getBlock(int x, int y, int z, Block mask = Blocks::AIR, Chunk* cptr = nullptr);
	Brightness getBrightness(int x, int y, int z, Chunk* cptr = nullptr);
	void setblock(int x, int y, int z, Block Block, Chunk* cptr = nullptr);
	void setbrightness(int x, int y, int z, Brightness Brightness, Chunk* cptr = nullptr);
	inline void pickleaf(){
		if (rnd() < 0.2) {
			if (rnd() < 0.5)Player::addItem(APPLE);
			else Player::addItem(STICK);
		}
		else {
			Player::addItem(Blocks::LEAF);
		}
	}
   
    void picktree(int x, int y, int z);
	inline void pickblock(int x, int y, int z) {
		if (getBlock(x, y, z) == Blocks::WOOD && 
			((getBlock(x, y+1, z) == Blocks::WOOD)|| (getBlock(x, y + 1, z) == Blocks::LEAF)) &&
			(getBlock(x, y, z + 1) == Blocks::AIR) && (getBlock(x, y, z - 1) == Blocks::AIR) &&
			(getBlock(x + 1, y, z) == Blocks::AIR) && (getBlock(x - 1, y, z) == Blocks::AIR) &&
			(getBlock(x, y - 1, z) != Blocks::AIR)
			) { picktree(x, y + 1, z); }//触发砍树模式
		//击打树叶
		if (getBlock(x, y, z)!=Blocks::LEAF)Player::addItem(getBlock(x, y, z));
		else pickleaf();

		setblock(x, y, z, Blocks::AIR); 
	}


	inline bool chunkInRange(int x, int y, int z, int px, int py, int pz, int dist) {
		//检测给出的chunk坐标是否在渲染范围内
		if (x<px - dist || x>px + dist - 1 || y<py - dist || y>py + dist - 1 || z<pz - dist || z>pz + dist - 1) return false;
		return true;
	}
	bool chunkUpdated(int x, int y, int z);
	void setChunkUpdated(int x, int y, int z, bool value);
	void sortChunkBuildRenderList(int xpos, int ypos, int zpos);
	void sortChunkLoadUnloadList(int xpos, int ypos, int zpos);
	void calcVisible(double xpos, double ypos, double zpos, Frustum& frus);

	void destroyAllChunks();

	void buildtree(int x, int y, int z);
	void explode(int x, int y, int z, int r, Chunk* c = nullptr);
}
