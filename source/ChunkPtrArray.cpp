// 
// NEWorld: ChunkPtrArray.cpp
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

#include "ChunkPtrArray.h"
#include <algorithm>
#include <memory>

namespace World {
    void CPARegionalCache::create(int s) {
        mSize3 = (mSize2 = (mSize1 = s) * s) * s;
        mCache = std::make_unique<Chunk*[]>(mSize3);
        std::fill_n(mCache.get(), mSize3, nullptr);
    }

    void CPARegionalCache::move(int xd, int yd, int zd) {
        if ((xd != 0) && (yd != 0) && (zd != 0)) {
            auto arrTemp = std::unique_ptr<Chunk*[]>(new Chunk*[mSize3]);
            for (int x = 0; x < mSize1; x++)
                for (int y = 0; y < mSize1; y++)
                    for (int z = 0; z < mSize1; z++)
                        if (elementExists(x + xd, y + yd, z + zd))
                            arrTemp[x * mSize2 + y * mSize1 + z] = mCache[(x + xd) * mSize2 + (y + yd) * mSize1 + (z +
                                zd)];
                        else
                            arrTemp[x * mSize2 + y * mSize1 + z] = nullptr;

            std::swap(mCache, arrTemp);
            mOriX += xd;
            mOriY += yd;
            mOriZ += zd;
        }
    }
} // namespace World
