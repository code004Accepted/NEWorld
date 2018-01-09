/*
* NEWorld: A free game with similar rules to Minecraft.
* Copyright (C) 2017-2018 NEWorld Team
*
* This file is part of NEWorld.
* NEWorld is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* NEWorld is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with NEWorld.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "HeightMap.h"
#include "WorldGen.h"
#include <algorithm>

namespace World {
    void HeightMap::setSize(int s) {
        size = s;
        size2 = size * size;
    }

    void HeightMap::create() {
        array = new int[size2];
        std::fill_n(array, size2, -1);
    }

    void HeightMap::destroy() {
        delete[] array;
        array = nullptr;
    }

    void HeightMap::move(int xd, int zd) {
        int* arrTemp = new int[size2];
        for (int x = 0; x < size; x++) {
            for (int z = 0; z < size; z++) {
                if (x + xd >= 0 && z + zd >= 0 && x + xd < size && z + zd < size)
                    arrTemp[x * size + z] = array[(x + xd) * size + (z + zd)];
                else arrTemp[x * size + z] = -1;
            }
        }
        delete[] array;
        array = arrTemp;
        originX += xd;
        originZ += zd;
    }

    void HeightMap::moveTo(int x, int z) { move(x - originX, z - originZ); }

    int HeightMap::getHeight(int x, int z) {
        x -= originX;
        z -= originZ;
        if (x < 0 || z < 0 || x >= size || z >= size)
            return WorldGen::getHeight(x + originX, z + originZ);
        if (array[x * size + z] == -1)
            array[x * size + z] = WorldGen::getHeight(x + originX, z + originZ);
        return array[x * size + z];
    }
}
