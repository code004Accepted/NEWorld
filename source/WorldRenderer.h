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
#include "StdInclude.h"
#include "World.h"
#include "Renderer.h"

namespace WorldRenderer {
    struct RenderChunk {
        int cx, cy, cz;
        vtxCount vertexes[4];
        VBOID vbuffers[4];
        double loadAnim;

        RenderChunk(World::Chunk* c, double TimeDelta) :
            cx(c->cx), cy(c->cy), cz(c->cz), loadAnim(c->loadAnim * pow(0.6, TimeDelta)) {
            memcpy(vbuffers, c->vbuffer, sizeof(vbuffers));
            memcpy(vertexes, c->vertexes, sizeof(vertexes));
        }
    };

    extern std::vector<RenderChunk> RenderChunkList;

    int ListRenderChunks(int cx, int cy, int cz, int renderdistance, double curtime, bool frustest = true);
    void RenderChunks(double x, double y, double z, int buffer);
}
