// 
// NEWorld: Frustum.h
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
#include "Hitbox.h"

class Frustum {
private:
    float frus[24], clip[16];
    float proj[16], modl[16];

public:
    //AABB with Float32 coords
    struct ChunkBox {
        float xmin, ymin, zmin;
        float xmax, ymax, zmax;
    };

    float* getProjMatrix() { return proj; }
    float* getModlMatrix() { return modl; }

    void loadIdentity();

    void MultMatrixTo(float* sum, float* a, float* b) {
        sum[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
        sum[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13];
        sum[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
        sum[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];
        sum[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12];
        sum[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13];
        sum[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];
        sum[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];
        sum[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12];
        sum[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13];
        sum[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14];
        sum[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15];
        sum[12] = a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12];
        sum[13] = a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13];
        sum[14] = a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14];
        sum[15] = a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15];
    }

    inline void multMatrix(float* a, float* b);

    void setPerspective(float FOV, float aspect, float Znear, float Zfar);
    void setOrtho(float left, float right, float top, float bottom, float Znear, float Zfar);
    void multRotate(float angle, float x, float y, float z);

    inline void normalize(int side);

    void update();
    bool frustumTest(const ChunkBox& aabb);
};