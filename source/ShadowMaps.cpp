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

#include "ShadowMaps.h"

namespace ShadowMaps {
    void BuildShadowMap(double xpos, double ypos, double zpos, double curtime) {
        int cx = World::getChunkPos((int)xpos), cy = World::getChunkPos((int)ypos), cz = World::getChunkPos((int)zpos);

        Renderer::StartShadowPass();
        glClear(GL_DEPTH_BUFFER_BIT);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_FOG);
        glDisable(GL_BLEND);
        float scale = 16.0f * sqrt(3.0f);
        float length = Renderer::shadowdist * scale;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-length, length, -length, length, -length, length);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotated(Renderer::sunlightXrot, 1.0, 0.0, 0.0);
        glRotated(Renderer::sunlightYrot, 0.0, 1.0, 0.0);

        WorldRenderer::ListRenderChunks(cx, cy, cz, Renderer::shadowdist + 1, curtime, false);
        MutexUnlock(Mutex);
        WorldRenderer::RenderChunks(xpos, ypos, zpos, 3);
        MutexLock(Mutex);

        glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
        glDisableClientState(GL_VERTEX_ARRAY);
        Renderer::EndShadowPass();

        glEnable(GL_FOG);
        glEnable(GL_BLEND);
    }

    void RenderShadowMap(double xpos, double ypos, double zpos, double curtime) {
        int cx = World::getChunkPos((int)xpos), cy = World::getChunkPos((int)ypos), cz = World::getChunkPos((int)zpos);

        bindShader(Renderer::DepthShader);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_FOG);
        glDisable(GL_BLEND);
        float scale = 16.0f * sqrt(3.0f);
        float length = Renderer::shadowdist * scale;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-length, length, -length, length, -length, length);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotated(Renderer::sunlightXrot, 1.0, 0.0, 0.0);
        glRotated(Renderer::sunlightYrot, 0.0, 1.0, 0.0);

        WorldRenderer::ListRenderChunks(cx, cy, cz, Renderer::shadowdist + 1, curtime, false);
        MutexUnlock(Mutex);
        WorldRenderer::RenderChunks(xpos, ypos, zpos, 3);
        MutexLock(Mutex);

        glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
        glDisableClientState(GL_VERTEX_ARRAY);
        Shader::unbind();

        glEnable(GL_FOG);
        glEnable(GL_BLEND);
    }
}
