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

#include "ChunkRenderer.h"
#include "Renderer.h"
#include "World.h"

namespace ChunkRenderer {
    using World::getBrightness;

    /*
    合并面的顶点顺序（以0到3标出）：

    The vertex order of merge face render
    Numbered from 0 to 3:

    (k++)
    ...
    |    |
    +----+--
    |    |
    |    |    |
    3----2----+-
    |curr|    |   ...
    |face|    |   (j++)
    0----1----+--

    --qiaozhanrong
    */

    void renderPrimitive(QuadPrimitive& p) {
        float col0 = static_cast<float>(p.col0) * 0.25f / World::BrightnessMax;
        float col1 = static_cast<float>(p.col1) * 0.25f / World::BrightnessMax;
        float col2 = static_cast<float>(p.col2) * 0.25f / World::BrightnessMax;
        float col3 = static_cast<float>(p.col3) * 0.25f / World::BrightnessMax;
        int x = p.x, y = p.y, z = p.z, length = p.length;
        Renderer::TexCoord3d(0.0, 0.0, (p.tex + 0.5) / 64.0);
        if (p.direction == 0) {
            if (Renderer::AdvancedRender) Renderer::Attrib1f(2.0f);
            else col0 *= 0.7f, col1 *= 0.7f, col2 *= 0.7f, col3 *= 0.7f;
            Renderer::Color3f(col0, col0, col0);
            Renderer::TexCoord2d(0.0, 0.0);
            Renderer::Vertex3d(x + 0.5, y - 0.5, z - 0.5);
            Renderer::Color3f(col1, col1, col1);
            Renderer::TexCoord2d(0.0, 1.0);
            Renderer::Vertex3d(x + 0.5, y + 0.5, z - 0.5);
            Renderer::Color3f(col2, col2, col2);
            Renderer::TexCoord2d(length + 1.0, 1.0);
            Renderer::Vertex3d(x + 0.5, y + 0.5, z + length + 0.5);
            Renderer::Color3f(col3, col3, col3);
            Renderer::TexCoord2d(length + 1.0, 0.0);
            Renderer::Vertex3d(x + 0.5, y - 0.5, z + length + 0.5);
        }
        else if (p.direction == 1) {
            if (Renderer::AdvancedRender) Renderer::Attrib1f(3.0f);
            else col0 *= 0.7f, col1 *= 0.7f, col2 *= 0.7f, col3 *= 0.7f;
            Renderer::Color3f(col0, col0, col0);
            Renderer::TexCoord2d(0.0, 1.0);
            Renderer::Vertex3d(x - 0.5, y + 0.5, z - 0.5);
            Renderer::Color3f(col1, col1, col1);
            Renderer::TexCoord2d(0.0, 0.0);
            Renderer::Vertex3d(x - 0.5, y - 0.5, z - 0.5);
            Renderer::Color3f(col2, col2, col2);
            Renderer::TexCoord2d(length + 1.0, 0.0);
            Renderer::Vertex3d(x - 0.5, y - 0.5, z + length + 0.5);
            Renderer::Color3f(col3, col3, col3);
            Renderer::TexCoord2d(length + 1.0, 1.0);
            Renderer::Vertex3d(x - 0.5, y + 0.5, z + length + 0.5);
        }
        else if (p.direction == 2) {
            if (Renderer::AdvancedRender) Renderer::Attrib1f(4.0f);
            Renderer::Color3f(col0, col0, col0);
            Renderer::TexCoord2d(0.0, 0.0);
            Renderer::Vertex3d(x + 0.5, y + 0.5, z - 0.5);
            Renderer::Color3f(col1, col1, col1);
            Renderer::TexCoord2d(0.0, 1.0);
            Renderer::Vertex3d(x - 0.5, y + 0.5, z - 0.5);
            Renderer::Color3f(col2, col2, col2);
            Renderer::TexCoord2d(length + 1.0, 1.0);
            Renderer::Vertex3d(x - 0.5, y + 0.5, z + length + 0.5);
            Renderer::Color3f(col3, col3, col3);
            Renderer::TexCoord2d(length + 1.0, 0.0);
            Renderer::Vertex3d(x + 0.5, y + 0.5, z + length + 0.5);
        }
        else if (p.direction == 3) {
            if (Renderer::AdvancedRender) Renderer::Attrib1f(5.0f);
            Renderer::Color3f(col0, col0, col0);
            Renderer::TexCoord2d(0.0, 0.0);
            Renderer::Vertex3d(x - 0.5, y - 0.5, z - 0.5);
            Renderer::Color3f(col1, col1, col1);
            Renderer::TexCoord2d(0.0, 1.0);
            Renderer::Vertex3d(x + 0.5, y - 0.5, z - 0.5);
            Renderer::Color3f(col2, col2, col2);
            Renderer::TexCoord2d(length + 1.0, 1.0);
            Renderer::Vertex3d(x + 0.5, y - 0.5, z + length + 0.5);
            Renderer::Color3f(col3, col3, col3);
            Renderer::TexCoord2d(length + 1.0, 0.0);
            Renderer::Vertex3d(x - 0.5, y - 0.5, z + length + 0.5);
        }
        else if (p.direction == 4) {
            if (Renderer::AdvancedRender) Renderer::Attrib1f(0.0f);
            else col0 *= 0.5f, col1 *= 0.5f, col2 *= 0.5f, col3 *= 0.5f;
            Renderer::Color3f(col0, col0, col0);
            Renderer::TexCoord2d(0.0, 1.0);
            Renderer::Vertex3d(x - 0.5, y + 0.5, z + 0.5);
            Renderer::Color3f(col1, col1, col1);
            Renderer::TexCoord2d(0.0, 0.0);
            Renderer::Vertex3d(x - 0.5, y - 0.5, z + 0.5);
            Renderer::Color3f(col2, col2, col2);
            Renderer::TexCoord2d(length + 1.0, 0.0);
            Renderer::Vertex3d(x + length + 0.5, y - 0.5, z + 0.5);
            Renderer::Color3f(col3, col3, col3);
            Renderer::TexCoord2d(length + 1.0, 1.0);
            Renderer::Vertex3d(x + length + 0.5, y + 0.5, z + 0.5);
        }
        else if (p.direction == 5) {
            if (Renderer::AdvancedRender) Renderer::Attrib1f(1.0f);
            else col0 *= 0.5f, col1 *= 0.5f, col2 *= 0.5f, col3 *= 0.5f;
            Renderer::Color3f(col0, col0, col0);
            Renderer::TexCoord2d(0.0, 0.0);
            Renderer::Vertex3d(x - 0.5, y - 0.5, z - 0.5);
            Renderer::Color3f(col1, col1, col1);
            Renderer::TexCoord2d(0.0, 1.0);
            Renderer::Vertex3d(x - 0.5, y + 0.5, z - 0.5);
            Renderer::Color3f(col2, col2, col2);
            Renderer::TexCoord2d(length + 1.0, 1.0);
            Renderer::Vertex3d(x + length + 0.5, y + 0.5, z - 0.5);
            Renderer::Color3f(col3, col3, col3);
            Renderer::TexCoord2d(length + 1.0, 0.0);
            Renderer::Vertex3d(x + length + 0.5, y - 0.5, z - 0.5);
        }
    }

    void RenderPrimitive_Depth(QuadPrimitiveDepth& p) {
        const int x = p.x, y = p.y, z = p.z, length = p.length;
        if (p.direction == 0) {
            Renderer::Vertex3d(x + 0.5, y - 0.5, z - 0.5);
            Renderer::Vertex3d(x + 0.5, y + 0.5, z - 0.5);
            Renderer::Vertex3d(x + 0.5, y + 0.5, z + length + 0.5);
            Renderer::Vertex3d(x + 0.5, y - 0.5, z + length + 0.5);
        }
        else if (p.direction == 1) {
            Renderer::Vertex3d(x - 0.5, y + 0.5, z - 0.5);
            Renderer::Vertex3d(x - 0.5, y - 0.5, z - 0.5);
            Renderer::Vertex3d(x - 0.5, y - 0.5, z + length + 0.5);
            Renderer::Vertex3d(x - 0.5, y + 0.5, z + length + 0.5);
        }
        else if (p.direction == 2) {
            Renderer::Vertex3d(x + 0.5, y + 0.5, z - 0.5);
            Renderer::Vertex3d(x - 0.5, y + 0.5, z - 0.5);
            Renderer::Vertex3d(x - 0.5, y + 0.5, z + length + 0.5);
            Renderer::Vertex3d(x + 0.5, y + 0.5, z + length + 0.5);
        }
        else if (p.direction == 3) {
            Renderer::Vertex3d(x - 0.5, y - 0.5, z - 0.5);
            Renderer::Vertex3d(x + 0.5, y - 0.5, z - 0.5);
            Renderer::Vertex3d(x + 0.5, y - 0.5, z + length + 0.5);
            Renderer::Vertex3d(x - 0.5, y - 0.5, z + length + 0.5);
        }
        else if (p.direction == 4) {
            Renderer::Vertex3d(x - 0.5, y + 0.5, z + 0.5);
            Renderer::Vertex3d(x - 0.5, y - 0.5, z + 0.5);
            Renderer::Vertex3d(x + length + 0.5, y - 0.5, z + 0.5);
            Renderer::Vertex3d(x + length + 0.5, y + 0.5, z + 0.5);
        }
        else if (p.direction == 5) {
            Renderer::Vertex3d(x - 0.5, y - 0.5, z - 0.5);
            Renderer::Vertex3d(x - 0.5, y + 0.5, z - 0.5);
            Renderer::Vertex3d(x + length + 0.5, y + 0.5, z - 0.5);
            Renderer::Vertex3d(x + length + 0.5, y - 0.5, z - 0.5);
        }
    }

    void RenderChunk(World::Chunk* c) {
        int x, y, z;
        if (Renderer::AdvancedRender) Renderer::Init(2, 3, 1);
        else Renderer::Init(2, 3);
        for (x = 0; x < 16; x++) {
            for (y = 0; y < 16; y++) {
                for (z = 0; z < 16; z++) {
                    const Block curr = c->getBlock(x, y, z);
                    if (curr == Blocks::AIR) continue;
                    if (!getBlockInfo(curr).isTranslucent()) renderblock(x, y, z, c);
                }
            }
        }
        Renderer::Flush(c->vbuffer[0], c->vertexes[0]);
        if (Renderer::AdvancedRender) Renderer::Init(2, 3, 1);
        else Renderer::Init(2, 3);
        for (x = 0; x < 16; x++) {
            for (y = 0; y < 16; y++) {
                for (z = 0; z < 16; z++) {
                    Block curr = c->getBlock(x, y, z);
                    if (curr == Blocks::AIR) continue;
                    if (getBlockInfo(curr).isTranslucent() && getBlockInfo(curr).isSolid()) renderblock(x, y, z, c);
                }
            }
        }
        Renderer::Flush(c->vbuffer[1], c->vertexes[1]);
        if (Renderer::AdvancedRender) Renderer::Init(2, 3, 1);
        else Renderer::Init(2, 3);
        for (x = 0; x < 16; x++) {
            for (y = 0; y < 16; y++) {
                for (z = 0; z < 16; z++) {
                    Block curr = c->getBlock(x, y, z);
                    if (curr == Blocks::AIR) continue;
                    if (!getBlockInfo(curr).isSolid()) renderblock(x, y, z, c);
                }
            }
        }
        Renderer::Flush(c->vbuffer[2], c->vertexes[2]);
    }

    //合并面大法好！！！
    void MergeFaceRender(World::Chunk* c) {
        //话说我注释一会中文一会英文是不是有点奇怪。。。
        // -- qiaozhanrong

        int cx = c->cx, cy = c->cy, cz = c->cz;
        int gx = 0, gy = 0, gz = 0;
        int x = 0, y = 0, z = 0, cur_l_mx, br;
        int col0 = 0, col1 = 0, col2 = 0, col3 = 0;
        QuadPrimitive cur;
        Block bl, neighbour;
        uint8_t face = 0;
        TextureID tex;
        bool valid = false;
        for (int steps = 0; steps < 3; steps++) {
            cur = QuadPrimitive();
            cur_l_mx = bl = neighbour = 0;
            //Linear merge
            if (Renderer::AdvancedRender) Renderer::Init(3, 3, 1);
            else Renderer::Init(3, 3);
            for (int d = 0; d < 6; d++) {
                cur.direction = d;
                if (d == 2) face = 1;
                else if (d == 3) face = 3;
                else face = 2;
                //Render current face
                for (int i = 0; i < 16; i++)
                    for (int j = 0; j < 16; j++) {
                        for (int k = 0; k < 16; k++) {
                            //Get position & brightness
                            if (d == 0) {
                                //x+
                                x = i, y = j, z = k;
                                gx = cx * 16 + x;
                                gy = cy * 16 + y;
                                gz = cz * 16 + z;
                                br = getBrightness(gx + 1, gy, gz, c);
                                if (SmoothLighting) {
                                    col0 = br + getBrightness(gx + 1, gy - 1, gz, c) + getBrightness(
                                        gx + 1, gy, gz - 1, c) + getBrightness(gx + 1, gy - 1, gz - 1, c);
                                    col1 = br + getBrightness(gx + 1, gy + 1, gz, c) + getBrightness(
                                        gx + 1, gy, gz - 1, c) + getBrightness(gx + 1, gy + 1, gz - 1, c);
                                    col2 = br + getBrightness(gx + 1, gy + 1, gz, c) + getBrightness(
                                        gx + 1, gy, gz + 1, c) + getBrightness(gx + 1, gy + 1, gz + 1, c);
                                    col3 = br + getBrightness(gx + 1, gy - 1, gz, c) + getBrightness(
                                        gx + 1, gy, gz + 1, c) + getBrightness(gx + 1, gy - 1, gz + 1, c);
                                }
                                else col0 = col1 = col2 = col3 = br * 4;
                            }
                            else if (d == 1) {
                                //x-
                                x = i, y = j, z = k;
                                gx = cx * 16 + x;
                                gy = cy * 16 + y;
                                gz = cz * 16 + z;
                                br = getBrightness(gx - 1, gy, gz, c);
                                if (SmoothLighting) {
                                    col0 = br + getBrightness(gx - 1, gy + 1, gz, c) + getBrightness(
                                        gx - 1, gy, gz - 1, c) + getBrightness(gx - 1, gy + 1, gz - 1, c);
                                    col1 = br + getBrightness(gx - 1, gy - 1, gz, c) + getBrightness(
                                        gx - 1, gy, gz - 1, c) + getBrightness(gx - 1, gy - 1, gz - 1, c);
                                    col2 = br + getBrightness(gx - 1, gy - 1, gz, c) + getBrightness(
                                        gx - 1, gy, gz + 1, c) + getBrightness(gx - 1, gy - 1, gz + 1, c);
                                    col3 = br + getBrightness(gx - 1, gy + 1, gz, c) + getBrightness(
                                        gx - 1, gy, gz + 1, c) + getBrightness(gx - 1, gy + 1, gz + 1, c);
                                }
                                else col0 = col1 = col2 = col3 = br * 4;
                            }
                            else if (d == 2) {
                                //y+
                                x = j, y = i, z = k;
                                gx = cx * 16 + x;
                                gy = cy * 16 + y;
                                gz = cz * 16 + z;
                                br = getBrightness(gx, gy + 1, gz, c);
                                if (SmoothLighting) {
                                    col0 = br + getBrightness(gx + 1, gy + 1, gz, c) + getBrightness(
                                        gx, gy + 1, gz - 1, c) + getBrightness(gx + 1, gy + 1, gz - 1, c);
                                    col1 = br + getBrightness(gx - 1, gy + 1, gz, c) + getBrightness(
                                        gx, gy + 1, gz - 1, c) + getBrightness(gx - 1, gy + 1, gz - 1, c);
                                    col2 = br + getBrightness(gx - 1, gy + 1, gz, c) + getBrightness(
                                        gx, gy + 1, gz + 1, c) + getBrightness(gx - 1, gy + 1, gz + 1, c);
                                    col3 = br + getBrightness(gx + 1, gy + 1, gz, c) + getBrightness(
                                        gx, gy + 1, gz + 1, c) + getBrightness(gx + 1, gy + 1, gz + 1, c);
                                }
                                else col0 = col1 = col2 = col3 = br * 4;
                            }
                            else if (d == 3) {
                                //y-
                                x = j, y = i, z = k;
                                gx = cx * 16 + x;
                                gy = cy * 16 + y;
                                gz = cz * 16 + z;
                                br = getBrightness(gx, gy - 1, gz, c);
                                if (SmoothLighting) {
                                    col0 = br + getBrightness(gx - 1, gy - 1, gz, c) + getBrightness(
                                        gx, gy - 1, gz - 1, c) + getBrightness(gx - 1, gy - 1, gz - 1, c);
                                    col1 = br + getBrightness(gx + 1, gy - 1, gz, c) + getBrightness(
                                        gx, gy - 1, gz - 1, c) + getBrightness(gx + 1, gy - 1, gz - 1, c);
                                    col2 = br + getBrightness(gx + 1, gy - 1, gz, c) + getBrightness(
                                        gx, gy - 1, gz + 1, c) + getBrightness(gx + 1, gy - 1, gz + 1, c);
                                    col3 = br + getBrightness(gx - 1, gy - 1, gz, c) + getBrightness(
                                        gx, gy - 1, gz + 1, c) + getBrightness(gx - 1, gy - 1, gz + 1, c);
                                }
                                else col0 = col1 = col2 = col3 = br * 4;
                            }
                            else if (d == 4) {
                                //z+
                                x = k, y = j, z = i;
                                gx = cx * 16 + x;
                                gy = cy * 16 + y;
                                gz = cz * 16 + z;
                                br = getBrightness(gx, gy, gz + 1, c);
                                if (SmoothLighting) {
                                    col0 = br + getBrightness(gx - 1, gy, gz + 1, c) + getBrightness(
                                        gx, gy + 1, gz + 1, c) + getBrightness(gx - 1, gy + 1, gz + 1, c);
                                    col1 = br + getBrightness(gx - 1, gy, gz + 1, c) + getBrightness(
                                        gx, gy - 1, gz + 1, c) + getBrightness(gx - 1, gy - 1, gz + 1, c);
                                    col2 = br + getBrightness(gx + 1, gy, gz + 1, c) + getBrightness(
                                        gx, gy - 1, gz + 1, c) + getBrightness(gx + 1, gy - 1, gz + 1, c);
                                    col3 = br + getBrightness(gx + 1, gy, gz + 1, c) + getBrightness(
                                        gx, gy + 1, gz + 1, c) + getBrightness(gx + 1, gy + 1, gz + 1, c);
                                }
                                else col0 = col1 = col2 = col3 = br * 4;
                            }
                            else if (d == 5) {
                                //z-
                                x = k, y = j, z = i;
                                gx = cx * 16 + x;
                                gy = cy * 16 + y;
                                gz = cz * 16 + z;
                                br = getBrightness(gx, gy, gz - 1, c);
                                if (SmoothLighting) {
                                    col0 = br + getBrightness(gx - 1, gy, gz - 1, c) + getBrightness(
                                        gx, gy - 1, gz - 1, c) + getBrightness(gx - 1, gy - 1, gz - 1, c);
                                    col1 = br + getBrightness(gx - 1, gy, gz - 1, c) + getBrightness(
                                        gx, gy + 1, gz - 1, c) + getBrightness(gx - 1, gy + 1, gz - 1, c);
                                    col2 = br + getBrightness(gx + 1, gy, gz - 1, c) + getBrightness(
                                        gx, gy + 1, gz - 1, c) + getBrightness(gx + 1, gy + 1, gz - 1, c);
                                    col3 = br + getBrightness(gx + 1, gy, gz - 1, c) + getBrightness(
                                        gx, gy - 1, gz - 1, c) + getBrightness(gx + 1, gy - 1, gz - 1, c);
                                }
                                else col0 = col1 = col2 = col3 = br * 4;
                            }
                            //Get block ID
                            bl = c->getBlock(x, y, z);
                            tex = Textures::getTextureIndex(bl, face);
                            neighbour = getBlock(gx + delta[d][0], gy + delta[d][1], gz + delta[d][2], Blocks::ROCK, c);
                            if (NiceGrass && bl == Blocks::GRASS) {
                                if (d == 0 && getBlock(gx + 1, gy - 1, gz, Blocks::ROCK, c) == Blocks::GRASS)
                                    tex =
                                        Textures::getTextureIndex(bl, 1);
                                else if (d == 1 && getBlock(gx - 1, gy - 1, gz, Blocks::ROCK, c) == Blocks::GRASS)
                                    tex =
                                        Textures::getTextureIndex(bl, 1);
                                else if (d == 4 && getBlock(gx, gy - 1, gz + 1, Blocks::ROCK, c) == Blocks::GRASS)
                                    tex =
                                        Textures::getTextureIndex(bl, 1);
                                else if (d == 5 && getBlock(gx, gy - 1, gz - 1, Blocks::ROCK, c) == Blocks::GRASS)
                                    tex =
                                        Textures::getTextureIndex(bl, 1);
                            }
                            //Render
                            const Blocks::SingleBlock& info = getBlockInfo(bl);
                            if (bl == Blocks::AIR || (bl == neighbour && bl != Blocks::LEAF) || getBlockInfo(neighbour).
                                isOpaque() ||
                                (steps == 0 && info.isTranslucent()) ||
                                (steps == 1 && (!info.isTranslucent() || !info.isSolid())) ||
                                (steps == 2 && (!info.isTranslucent() || info.isSolid()))) {
                                //Not valid block
                                if (valid) {
                                    if (getBlockInfo(neighbour).isOpaque() && !cur.once) {
                                        if (cur_l_mx < cur.length) cur_l_mx = cur.length;
                                        cur_l_mx++;
                                    }
                                    else {
                                        renderPrimitive(cur);
                                        valid = false;
                                    }
                                }
                                continue;
                            }
                            if (valid) {
                                if (col0 != col1 || col1 != col2 || col2 != col3 || cur.once || tex != cur.tex || col0
                                    != cur.col0) {
                                    renderPrimitive(cur);
                                    cur.x = x;
                                    cur.y = y;
                                    cur.z = z;
                                    cur.length = cur_l_mx = 0;
                                    cur.tex = tex;
                                    cur.col0 = col0;
                                    cur.col1 = col1;
                                    cur.col2 = col2;
                                    cur.col3 = col3;
                                    if (col0 != col1 || col1 != col2 || col2 != col3) cur.once = true;
                                    else cur.once = false;
                                }
                                else {
                                    if (cur_l_mx > cur.length) cur.length = cur_l_mx;
                                    cur.length++;
                                }
                            }
                            else {
                                valid = true;
                                cur.x = x;
                                cur.y = y;
                                cur.z = z;
                                cur.length = cur_l_mx = 0;
                                cur.tex = tex;
                                cur.col0 = col0;
                                cur.col1 = col1;
                                cur.col2 = col2;
                                cur.col3 = col3;
                                if (col0 != col1 || col1 != col2 || col2 != col3) cur.once = true;
                                else cur.once = false;
                            }
                        }
                        if (valid) {
                            renderPrimitive(cur);
                            valid = false;
                        }
                    }
            }
            Renderer::Flush(c->vbuffer[steps], c->vertexes[steps]);
        }
    }

    void RenderDepthModel(World::Chunk* c) {
        int cx = c->cx, cy = c->cy, cz = c->cz;
        int x = 0, y = 0, z = 0;
        QuadPrimitiveDepth cur;
        int cur_l_mx;
        Block bl, neighbour;
        bool valid = false;
        cur_l_mx = bl = neighbour = 0;
        //Linear merge for depth model
        Renderer::Init(0, 0);
        for (int d = 0; d < 6; d++) {
            cur.direction = d;
            for (int i = 0; i < 16; i++)
                for (int j = 0; j < 16; j++) {
                    for (int k = 0; k < 16; k++) {
                        //Get position
                        if (d < 2) x = i, y = j, z = k;
                        else if (d < 4) x = i, y = j, z = k;
                        else x = k, y = i, z = j;
                        //Get block ID
                        bl = c->getBlock(x, y, z);
                        //Get neighbour ID
                        int xx = x + delta[d][0], yy = y + delta[d][1], zz = z + delta[d][2];
                        int gx = cx * 16 + xx, gy = cy * 16 + yy, gz = cz * 16 + zz;
                        if (xx < 0 || xx >= 16 || yy < 0 || yy >= 16 || zz < 0 || zz >= 16)
                            neighbour = World::getBlock(gx, gy, gz);
                        else neighbour = c->getBlock(xx, yy, zz);
                        //Render
                        if (bl == Blocks::AIR || bl == Blocks::GLASS || (bl == neighbour && bl != Blocks::LEAF) ||
                            getBlockInfo(neighbour).isOpaque() || getBlockInfo(bl).isTranslucent()) {
                            //Not valid block
                            if (valid) {
                                if (getBlockInfo(neighbour).isOpaque()) {
                                    if (cur_l_mx < cur.length) cur_l_mx = cur.length;
                                    cur_l_mx++;
                                }
                                else {
                                    RenderPrimitive_Depth(cur);
                                    valid = false;
                                }
                            }
                            continue;
                        }
                        if (valid) {
                            if (cur_l_mx > cur.length) cur.length = cur_l_mx;
                            cur.length++;
                        }
                        else {
                            valid = true;
                            cur.x = x;
                            cur.y = y;
                            cur.z = z;
                            cur.length = cur_l_mx = 0;
                        }
                    }
                    if (valid) {
                        RenderPrimitive_Depth(cur);
                        valid = false;
                    }
                }
        }
        Renderer::Flush(c->vbuffer[3], c->vertexes[3]);
    }
}
