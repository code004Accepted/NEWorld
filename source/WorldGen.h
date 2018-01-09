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

#pragma once
#include "Definitions.h"

//Perlin Noise 2D
namespace WorldGen {
    extern double perm[256];
    extern int seed;
    extern double NoiseScaleX;
    extern double NoiseScaleZ;
    extern int WaterLevel;

    void perlinNoiseInit(int mapseed);

    inline double Noise(int x, int y) {
        long long xx = x + y * 13258953287;
        xx = (xx >> 13) ^ xx;
        return ((xx * (xx * xx * 15731 + 789221) + 1376312589) & 0x7fffffff) / 16777216.0;
    }

    double SmoothedNoise(int x, int y);
    inline double Interpolate(double a, double b, double x) { return a * (1.0 - x) + b * x; }
    double InterpolatedNoise(double x, double y);
    double PerlinNoise2D(double x, double y);

    inline int getHeight(int x, int y) {
#ifdef NEWORLD_DEBUG_PERFORMANCE_REC
        c_getHeightFromWorldGen++;
#endif
        return (int)PerlinNoise2D(x / NoiseScaleX + 0.125, y / NoiseScaleZ + 0.125) >> 2;
    }
}
