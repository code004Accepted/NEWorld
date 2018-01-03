#pragma once

#include <memory>

namespace World {
    class Chunk;
    class CPARegionalCache{
    public:
        void create(int s);
        void move(int xd, int yd, int zd);
        void moveTo(int x, int y, int z) { move(x - mOriX, y - mOriY, z - mOriZ); }
        Chunk* get(int x, int y, int z) const noexcept {
            x -= mOriX; y -= mOriY; z -= mOriZ;
            return elementExists(x, y, z)? mCache[x * mSize2 + y * mSize1 + z] : nullptr;
        }
        void set(int x, int y, int z, Chunk* c) noexcept {
            x -= mOriX; y -= mOriY; z -= mOriZ;
            if (elementExists(x, y, z)) mCache[x * mSize2 + y * mSize1 + z] = c;
        }
        void AddChunk(Chunk* cptr, int cx, int cy, int cz) noexcept { set(cx, cy, cz, cptr); }
        void DeleteChunk(int cx, int cy, int cz) noexcept { set(cx, cy, cz, nullptr); }
    private:
        bool elementExists(int x, int y, int z) const noexcept {
            return x >= 0 && x < mSize1 && z >= 0 && z < mSize1 && y >= 0 && y < mSize1;
        }
        std::unique_ptr<Chunk*[]> mCache { nullptr };
        int mOriX, mOriY, mOriZ, mSize1, mSize2, mSize3;
    };
}  // namespace World
