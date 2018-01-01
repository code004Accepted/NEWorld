#include "chunkPtrArray.h"
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
            for (int x = 0; x < mSize1; x++) {
                for (int y = 0; y < mSize1; y++) {
                    for (int z = 0; z < mSize1; z++) {
                        if (elementExists(x + xd, y + yd, z + zd)) {
                            arrTemp[x * mSize2 + y * mSize1 + z] = mCache[(x + xd) * mSize2 + (y + yd) * mSize1 + (z + zd)];
                        } else {
                            arrTemp[x * mSize2 + y * mSize1 + z] = nullptr;
}
}
}
}
            std::swap(mCache, arrTemp);
            mOriX += xd; mOriY += yd; mOriZ += zd;
        }
    }
}  // namespace World
