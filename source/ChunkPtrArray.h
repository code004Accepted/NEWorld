// 
// NEWorld: ChunkPtrArray.h
// NEWorld: A Free Game with Similar Rules to Minecraft.
// Copyright (C) 2015-2018 NEWorld Team
// 
// NEWorld is free software: you can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or 
// (at your option) any later version.
// 
// NEWorld is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General 
// Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with NEWorld.  If not, see <http://www.gnu.org/licenses/>.
// 

#pragma once

#include <memory>

namespace World {
    class Chunk;

    class CPARegionalCache {
    public:
        void create(int s);
        void move(int xd, int yd, int zd);
        void moveTo(int x, int y, int z) { move(x - mOriX, y - mOriY, z - mOriZ); }

        Chunk* get(int x, int y, int z) const noexcept {
            x -= mOriX;
            y -= mOriY;
            z -= mOriZ;
            return elementExists(x, y, z) ? mCache[x * mSize2 + y * mSize1 + z] : nullptr;
        }

        void set(int x, int y, int z, Chunk* c) noexcept {
            x -= mOriX;
            y -= mOriY;
            z -= mOriZ;
            if (elementExists(x, y, z)) mCache[x * mSize2 + y * mSize1 + z] = c;
        }

        void AddChunk(Chunk* cptr, int cx, int cy, int cz) noexcept { set(cx, cy, cz, cptr); }
        void DeleteChunk(int cx, int cy, int cz) noexcept { set(cx, cy, cz, nullptr); }
    private:
        bool elementExists(int x, int y, int z) const noexcept {
            return x >= 0 && x < mSize1 && z >= 0 && z < mSize1 && y >= 0 && y < mSize1;
        }

        std::unique_ptr<Chunk*[]> mCache{nullptr};
        int mOriX, mOriY, mOriZ, mSize1, mSize2, mSize3;
    };
} // namespace World
