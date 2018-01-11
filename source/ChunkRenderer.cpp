// 
// NEWorld: ChunkRenderer.cpp
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

#include "ChunkRenderer.h"
#include "Renderer.h"
#include "World.h"

namespace ChunkRenderer {
    using namespace World;
    using namespace Renderer;

    VertexArray va(262144, VertexFormat(3, 3, 0, 3, 1));

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

    void renderPrimitive(const QuadPrimitive& p) {
        auto col0 = static_cast<float>(p.col0) * 0.25f / BrightnessMax;
        auto col1 = static_cast<float>(p.col1) * 0.25f / BrightnessMax;
        auto col2 = static_cast<float>(p.col2) * 0.25f / BrightnessMax;
        auto col3 = static_cast<float>(p.col3) * 0.25f / BrightnessMax;
        const float x = p.x, y = p.y, z = p.z, length = p.length;
        const float texBase = (p.tex + 0.5) / 64.0;
        switch (p.direction) {
        case 0:
            col0 *= 0.7f, col1 *= 0.7f, col2 *= 0.7f, col3 *= 0.7f;
            va.addPrimitive(4, {
                0.0, 0.0, texBase, col0, col0, col0, x + 0.5f, y - 0.5f, z - 0.5f, 0.0f,
                0.0, 1.0, texBase, col1, col1, col1, x + 0.5f, y + 0.5f, z - 0.5f, 0.0f,
                length + 1.0f, 1.0, texBase, col2, col2, col2, x + 0.5f, y + 0.5f, z + length + 0.5f, 0.0f,
                length + 1.0f, 0.0, texBase, col3, col3, col3, x + 0.5f, y - 0.5f, z + length + 0.5f, 0.0f
            });
            break;
        case 1:
            col0 *= 0.7f, col1 *= 0.7f, col2 *= 0.7f, col3 *= 0.7f;
            va.addPrimitive(4, {
                0.0, 1.0, texBase, col0, col0, col0, x - 0.5f, y + 0.5f, z - 0.5f, 1.0f,
                0.0, 0.0, texBase, col1, col1, col1, x - 0.5f, y - 0.5f, z - 0.5f, 1.0f,
                length + 1.0f, 0.0, texBase, col2, col2, col2, x - 0.5f, y - 0.5f, z + length + 0.5f, 1.0f,
                length + 1.0f, 1.0, texBase, col3, col3, col3, x - 0.5f, y + 0.5f, z + length + 0.5f, 1.0f
            });
            break;
        case 2:
            va.addPrimitive(4, {
                0.0, 0.0, texBase, col0, col0, col0, x + 0.5f, y + 0.5f, z - 0.5f, 2.0f,
                0.0, 1.0, texBase, col1, col1, col1, x - 0.5f, y + 0.5f, z - 0.5f, 2.0f,
                length + 1.0f, 1.0, texBase, col2, col2, col2, x - 0.5f, y + 0.5f, z + length + 0.5f, 2.0f,
                length + 1.0f, 0.0, texBase, col3, col3, col3, x + 0.5f, y + 0.5f, z + length + 0.5f, 2.0f
            });
            break;
        case 3:
            va.addPrimitive(4, {
                0.0, 0.0, texBase, col0, col0, col0, x - 0.5f, y - 0.5f, z - 0.5f, 3.0f,
                0.0, 1.0, texBase, col1, col1, col1, x + 0.5f, y - 0.5f, z - 0.5f, 3.0f,
                length + 1.0f, 1.0, texBase, col2, col2, col2, x + 0.5f, y - 0.5f, z + length + 0.5f, 3.0f,
                length + 1.0f, 0.0, texBase, col3, col3, col3, x - 0.5f, y - 0.5f, z + length + 0.5f, 3.0f
            });
            break;
        case 4:
            col0 *= 0.5f, col1 *= 0.5f, col2 *= 0.5f, col3 *= 0.5f;
            va.addPrimitive(4, {
                0.0, 1.0, texBase, col0, col0, col0, x - 0.5f, y + 0.5f, z + 0.5f, 4.0f,
                0.0, 0.0, texBase, col1, col1, col1, x - 0.5f, y - 0.5f, z + 0.5f, 4.0f,
                length + 1.0f, 0.0, texBase, col2, col2, col2, x + length + 0.5f, y - 0.5f, z + 0.5f, 4.0f,
                length + 1.0f, 1.0, texBase, col3, col3, col3, x + length + 0.5f, y + 0.5f, z + 0.5f, 4.0f
            });
            break;
        case 5:
            col0 *= 0.5f, col1 *= 0.5f, col2 *= 0.5f, col3 *= 0.5f;
            va.addPrimitive(4, {
                0.0, 0.0, texBase, col0, col0, col0, x - 0.5f, y - 0.5f, z - 0.5f, 5.0f,
                0.0, 1.0, texBase, col1, col1, col1, x - 0.5f, y + 0.5f, z - 0.5f, 5.0f,
                length + 1.0f, 1.0, texBase, col2, col2, col2, x + length + 0.5f, y + 0.5f, z - 0.5f, 5.0f,
                length + 1.0f, 0.0, texBase, col3, col3, col3, x + length + 0.5f, y - 0.5f, z - 0.5f, 5.0f
            });
        default: ;
        };
    }

    void renderPrimitiveDepth(const QuadPrimitiveDepth& p) {
        const auto x = p.x, y = p.y, z = p.z, length = p.length;
        switch (p.direction) {
        case 0:
            va.addPrimitive(4, {
                x + 0.5f, y - 0.5f, z - 0.5f, x + 0.5f, y + 0.5f, z - 0.5f,
                x + 0.5f, y + 0.5f, z + length + 0.5f, x + 0.5f, y - 0.5f, z + length + 0.5f
            });
            break;
        case 1:
            va.addPrimitive(4, {
                x - 0.5f, y + 0.5f, z - 0.5f, x - 0.5f, y - 0.5f, z - 0.5f,
                x - 0.5f, y - 0.5f, z + length + 0.5f, x - 0.5f, y + 0.5f, z + length + 0.5f
            });
            break;
        case 2:
            va.addPrimitive(4, {
                x + 0.5f, y + 0.5f, z - 0.5f, x - 0.5f, y + 0.5f, z - 0.5f,
                x - 0.5f, y + 0.5f, z + length + 0.5f, x + 0.5f, y + 0.5f, z + length + 0.5f
            });
            break;
        case 3:
            va.addPrimitive(4, {
                x - 0.5f, y - 0.5f, z - 0.5f, x + 0.5f, y - 0.5f, z - 0.5f,
                x + 0.5f, y - 0.5f, z + length + 0.5f, x - 0.5f, y - 0.5f, z + length + 0.5f
            });
            break;
        case 4:
            va.addPrimitive(4, {
                x - 0.5f, y + 0.5f, z + 0.5f, x - 0.5f, y - 0.5f, z + 0.5f,
                x + length + 0.5f, y - 0.5f, z + 0.5f, x + length + 0.5f, y + 0.5f, z + 0.5f
            });
            break;
        case 5:
            va.addPrimitive(4, {
                x - 0.5f, y - 0.5f, z - 0.5f, x - 0.5f, y + 0.5f, z - 0.5f,
                x + length + 0.5f, y + 0.5f, z - 0.5f, x + length + 0.5f, y - 0.5f, z - 0.5f
            });
        default: ;
        };
    }

    //合并面大法好！！！
    void mergeFaceRender(Chunk* c) {
        //话说我注释一会中文一会英文是不是有点奇怪。。。
        // -- qiaozhanrong
        constexpr VertexFormat fmt(3, 3, 0, 3, 1);
        int cx = c->cx, cy = c->cy, cz = c->cz;
        int gx = 0, gy = 0, gz = 0;
        int x = 0, y = 0, z = 0, br;
        int col0 = 0, col1 = 0, col2 = 0, col3 = 0;
        Block bl, neighbour;
        uint8_t face = 0;
        bool valid = false;
        for (int steps = 0; steps < 3; steps++) {
            QuadPrimitive cur {};
            int curLMx = bl = neighbour = 0;
            //Linear merge
            va.setFormat(fmt);
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
                            TextureID tex = Textures::getTextureIndex(bl, face);
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
                                        if (curLMx < cur.length) curLMx = cur.length;
                                        curLMx++;
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
                                    cur.length = curLMx = 0;
                                    cur.tex = tex;
                                    cur.col0 = col0;
                                    cur.col1 = col1;
                                    cur.col2 = col2;
                                    cur.col3 = col3;
                                    if (col0 != col1 || col1 != col2 || col2 != col3) cur.once = true;
                                    else cur.once = false;
                                }
                                else {
                                    if (curLMx > cur.length) cur.length = curLMx;
                                    cur.length++;
                                }
                            }
                            else {
                                valid = true;
                                cur.x = x;
                                cur.y = y;
                                cur.z = z;
                                cur.length = curLMx = 0;
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
            c->vbo[steps].update(va);
        }
    }

    void renderDepthModel(Chunk* c) {
        constexpr VertexFormat fmt(0, 0, 0, 3);
        int cx = c->cx, cy = c->cy, cz = c->cz;
        int x = 0, y = 0, z = 0;
        QuadPrimitiveDepth cur;
        Block bl, neighbour;
        bool valid = false;
        int cur_l_mx = bl = neighbour = 0;
        //Linear merge for depth model
        va.setFormat(fmt);
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
                            neighbour = getBlock(gx, gy, gz);
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
                                    renderPrimitiveDepth(cur);
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
                        renderPrimitiveDepth(cur);
                        valid = false;
                    }
                }
        }
        c->vbo[3].update(va);
    }


    void renderblock(int x, int y, int z, Chunk* chunkptr) {
        float colors, color1, color2, color3, color4, tcx, tcy;
        int cx = chunkptr->cx, cy = chunkptr->cy, cz = chunkptr->cz;
        int gx = cx * 16 + x, gy = cy * 16 + y, gz = cz * 16 + z;
        Block blk[7] = {
            chunkptr->getBlock(x, y, z),
            z < 15 ? chunkptr->getBlock(x, y, z + 1) : getBlock(gx, gy, gz + 1, Blocks::ROCK),
            z > 0 ? chunkptr->getBlock(x, y, z - 1) : getBlock(gx, gy, gz - 1, Blocks::ROCK),
            x < 15 ? chunkptr->getBlock(x + 1, y, z) : getBlock(gx + 1, gy, gz, Blocks::ROCK),
            x > 0 ? chunkptr->getBlock(x - 1, y, z) : getBlock(gx - 1, gy, gz, Blocks::ROCK),
            y < 15 ? chunkptr->getBlock(x, y + 1, z) : getBlock(gx, gy + 1, gz, Blocks::ROCK),
            y > 0 ? chunkptr->getBlock(x, y - 1, z) : getBlock(gx, gy - 1, gz, Blocks::ROCK)
        };

        Brightness brt[7] = {
            chunkptr->getBrightness(x, y, z),
            z < 15 ? chunkptr->getBrightness(x, y, z + 1) : getBrightness(gx, gy, gz + 1),
            z > 0 ? chunkptr->getBrightness(x, y, z - 1) : getBrightness(gx, gy, gz - 1),
            x < 15 ? chunkptr->getBrightness(x + 1, y, z) : getBrightness(gx + 1, gy, gz),
            x > 0 ? chunkptr->getBrightness(x - 1, y, z) : getBrightness(gx - 1, gy, gz),
            y < 15 ? chunkptr->getBrightness(x, y + 1, z) : getBrightness(gx, gy + 1, gz),
            y > 0 ? chunkptr->getBrightness(x, y - 1, z) : getBrightness(gx, gy - 1, gz)
        };

        constexpr auto size = 1 / 8.0f;

        if (NiceGrass && blk[0] == Blocks::GRASS && getBlock(gx, gy - 1, gz + 1, Blocks::ROCK, chunkptr) == Blocks::
            GRASS) {
            tcx = Textures::getTexcoordX(blk[0], 1);
            tcy = Textures::getTexcoordY(blk[0], 1);
        }
        else {
            tcx = Textures::getTexcoordX(blk[0], 2);
            tcy = Textures::getTexcoordY(blk[0], 2);
        }

        // Front Face
        if (!(getBlockInfo(blk[1])
                .
                isOpaque() || (blk[1] == blk[0] &&
                    !getBlockInfo(blk[0]).isOpaque()
                )
            )
            ||
            blk[0] == Blocks::LEAF
        ) {
            colors = brt[1];
            color1 = colors;
            color2 = colors;
            color3 = colors;
            color4 = colors;

            if (blk[0] != Blocks::GLOWSTONE && SmoothLighting) {
                color1 = (colors + getBrightness(gx, gy - 1, gz + 1) + getBrightness(gx - 1, gy, gz + 1) +
                    getBrightness(gx - 1, gy - 1, gz + 1)) / 4.0;
                color2 = (colors + getBrightness(gx, gy - 1, gz + 1) + getBrightness(gx + 1, gy, gz + 1) +
                    getBrightness(gx + 1, gy - 1, gz + 1)) / 4.0;
                color3 = (colors + getBrightness(gx, gy + 1, gz + 1) + getBrightness(gx + 1, gy, gz + 1) +
                    getBrightness(gx + 1, gy + 1, gz + 1)) / 4.0;
                color4 = (colors + getBrightness(gx, gy + 1, gz + 1) + getBrightness(gx - 1, gy, gz + 1) +
                    getBrightness(gx - 1, gy + 1, gz + 1)) / 4.0;
            }

            color1 /= BrightnessMax;
            color2 /= BrightnessMax;
            color3 /= BrightnessMax;
            color4 /= BrightnessMax;
            if (blk[0] != Blocks::GLOWSTONE && !AdvancedRender) {
                color1 *= 0.5;
                color2 *= 0.5;
                color3 *= 0.5;
                color4 *= 0.5;
            }

            va.addPrimitive(4, {
                tcx, tcy, color1, color1, color1, -0.5f+ x, -0.5f+ y, 0.5f+ z, 0.0f,
                tcx + size, tcy, color2, color2, color2, 0.5f+ x, -0.5f+ y, 0.5f+ z, 0.0f,
                tcx + size, tcy + size, color3, color3, color3, 0.5f+ x, 0.5f+ y, 0.5f+ z, 0.0f,
                tcx, tcy + size, color4, color4, color4, -0.5f+ x, 0.5f+ y, 0.5f+ z, 0.0f
            });
        }

        if (NiceGrass && blk[0] == Blocks::GRASS && getBlock(gx, gy - 1, gz - 1, Blocks::ROCK, chunkptr) == Blocks::
            GRASS) {
            tcx = Textures::getTexcoordX(blk[0], 1);
            tcy = Textures::getTexcoordY(blk[0], 1);
        }
        else {
            tcx = Textures::getTexcoordX(blk[0], 2);
            tcy = Textures::getTexcoordY(blk[0], 2);
        }

        // Back Face
        if (!(getBlockInfo(blk[2]).isOpaque() || (blk[2] == blk[0] && !getBlockInfo(blk[0]).isOpaque()
                )
            )
            ||
            blk[0] == Blocks::LEAF
        ) {
            colors = brt[2];
            color1 = colors;
            color2 = colors;
            color3 = colors;
            color4 = colors;

            if (blk[0] != Blocks::GLOWSTONE && SmoothLighting) {
                color1 = (colors + getBrightness(gx, gy - 1, gz - 1) + getBrightness(gx - 1, gy, gz - 1) +
                    getBrightness(gx - 1, gy - 1, gz - 1)) / 4.0;
                color2 = (colors + getBrightness(gx, gy + 1, gz - 1) + getBrightness(gx - 1, gy, gz - 1) +
                    getBrightness(gx - 1, gy + 1, gz - 1)) / 4.0;
                color3 = (colors + getBrightness(gx, gy + 1, gz - 1) + getBrightness(gx + 1, gy, gz - 1) +
                    getBrightness(gx + 1, gy + 1, gz - 1)) / 4.0;
                color4 = (colors + getBrightness(gx, gy - 1, gz - 1) + getBrightness(gx + 1, gy, gz - 1) +
                    getBrightness(gx + 1, gy - 1, gz - 1)) / 4.0;
            }

            color1 /= BrightnessMax;
            color2 /= BrightnessMax;
            color3 /= BrightnessMax;
            color4 /= BrightnessMax;
            if (blk[0] != Blocks::GLOWSTONE && !AdvancedRender) {
                color1 *= 0.5;
                color2 *= 0.5;
                color3 *= 0.5;
                color4 *= 0.5;
            }

            va.addPrimitive(4, {
                tcx + size, tcy, color1, color1, color1, -0.5f+ x, -0.5f+ y, -0.5f+ z, 1.0f,
                tcx + size, tcy + size, color2, color2, color2, -0.5f+ x, 0.5f+ y, -0.5f+ z, 1.0f,
                tcx, tcy + size, color3, color3, color3, 0.5f+ x, 0.5f+ y, -0.5f+ z, 1.0f,
                tcx, tcy, color4, color4, color4, 0.5f+ x, -0.5f+ y, -0.5f+ z, 1.0f
            });
        }

        if (NiceGrass && blk[0] == Blocks::GRASS && getBlock(gx + 1, gy - 1, gz, Blocks::ROCK, chunkptr) == Blocks::
            GRASS) {
            tcx = Textures::getTexcoordX(blk[0], 1);
            tcy = Textures::getTexcoordY(blk[0], 1);
        }
        else {
            tcx = Textures::getTexcoordX(blk[0], 2);
            tcy = Textures::getTexcoordY(blk[0], 2);
        }

        // Right face
        if (!(getBlockInfo(blk[3])
                .
                isOpaque() || (blk[3] == blk[0] && !
                    getBlockInfo(blk[0]).
                    isOpaque()
                )
            )
            ||
            blk[0] == Blocks::LEAF
        ) {
            colors = brt[3];
            color1 = colors;
            color2 = colors;
            color3 = colors;
            color4 = colors;

            if (blk[0] != Blocks::GLOWSTONE && SmoothLighting) {
                color1 = (colors + getBrightness(gx + 1, gy - 1, gz) + getBrightness(gx + 1, gy, gz - 1) +
                    getBrightness(gx + 1, gy - 1, gz - 1)) / 4.0;
                color2 = (colors + getBrightness(gx + 1, gy + 1, gz) + getBrightness(gx + 1, gy, gz - 1) +
                    getBrightness(gx + 1, gy + 1, gz - 1)) / 4.0;
                color3 = (colors + getBrightness(gx + 1, gy + 1, gz) + getBrightness(gx + 1, gy, gz + 1) +
                    getBrightness(gx + 1, gy + 1, gz + 1)) / 4.0;
                color4 = (colors + getBrightness(gx + 1, gy - 1, gz) + getBrightness(gx + 1, gy, gz + 1) +
                    getBrightness(gx + 1, gy - 1, gz + 1)) / 4.0;
            }

            color1 /= BrightnessMax;
            color2 /= BrightnessMax;
            color3 /= BrightnessMax;
            color4 /= BrightnessMax;
            if (blk[0] != Blocks::GLOWSTONE && !AdvancedRender) {
                color1 *= 0.7;
                color2 *= 0.7;
                color3 *= 0.7;
                color4 *= 0.7;
            }

            va.addPrimitive(4, {
                tcx + size, tcy, color1, color1, color1, 0.5f+ x, -0.5f+ y, -0.5f+ z, 2.0f,
                tcx + size, tcy + size, color2, color2, color2, 0.5f+ x, 0.5f+ y, -0.5f+ z, 2.0f,
                tcx, tcy + size, color3, color3, color3, 0.5f+ x, 0.5f+ y, 0.5f+ z, 2.0f,
                tcx, tcy, color4, color4, color4, 0.5f+ x, -0.5f+ y, 0.5f+ z, 2.0f
            });
        }

        if (NiceGrass && blk[0] == Blocks::GRASS && getBlock(gx - 1, gy - 1, gz, Blocks::ROCK, chunkptr) == Blocks::
            GRASS) {
            tcx = Textures::getTexcoordX(blk[0], 1);
            tcy = Textures::getTexcoordY(blk[0], 1);
        }
        else {
            tcx = Textures::getTexcoordX(blk[0], 2);
            tcy = Textures::getTexcoordY(blk[0], 2);
        }

        // Left Face
        if (!(getBlockInfo(blk[4])
                .
                isOpaque() || (blk[4] == blk[0] &&
                    !getBlockInfo(blk[0]).isOpaque()
                )
            )
            ||
            blk[0] == Blocks::LEAF
        ) {
            colors = brt[4];
            color1 = colors;
            color2 = colors;
            color3 = colors;
            color4 = colors;

            if (blk[0] != Blocks::GLOWSTONE && SmoothLighting) {
                color1 = (colors + getBrightness(gx - 1, gy - 1, gz) + getBrightness(gx - 1, gy, gz - 1) +
                    getBrightness(gx - 1, gy - 1, gz - 1)) / 4.0;
                color2 = (colors + getBrightness(gx - 1, gy - 1, gz) + getBrightness(gx - 1, gy, gz + 1) +
                    getBrightness(gx - 1, gy - 1, gz + 1)) / 4.0;
                color3 = (colors + getBrightness(gx - 1, gy + 1, gz) + getBrightness(gx - 1, gy, gz + 1) +
                    getBrightness(gx - 1, gy + 1, gz + 1)) / 4.0;
                color4 = (colors + getBrightness(gx - 1, gy + 1, gz) + getBrightness(gx - 1, gy, gz - 1) +
                    getBrightness(gx - 1, gy + 1, gz - 1)) / 4.0;
            }

            color1 /= BrightnessMax;
            color2 /= BrightnessMax;
            color3 /= BrightnessMax;
            color4 /= BrightnessMax;
            if (blk[0] != Blocks::GLOWSTONE && !AdvancedRender) {
                color1 *= 0.7;
                color2 *= 0.7;
                color3 *= 0.7;
                color4 *= 0.7;
            }

            va.addPrimitive(4, {
                tcx, tcy, color1, color1, color1, -0.5f+ x, -0.5f+ y, -0.5f+ z, 3.0f,
                tcx + size, tcy, color2, color2, color2, -0.5f+ x, -0.5f+ y, 0.5f+ z, 3.0f,
                tcx + size, tcy + size, color3, color3, color3, -0.5f+ x, 0.5f+ y, 0.5f+ z, 3.0f,
                tcx, tcy + size, color4, color4, color4, -0.5f+ x, 0.5f+ y, -0.5f+ z, 3.0f
            });
        }

        tcx = Textures::getTexcoordX(blk[0], 1);
        tcy = Textures::getTexcoordY(blk[0], 1);

        // Top Face
        if (!(getBlockInfo(blk[5])
                .
                isOpaque() || (blk[5] == blk[0] &&
                    !getBlockInfo(blk[0]).isOpaque()
                )
            )
            ||
            blk[0] == Blocks::LEAF
        ) {
            colors = brt[5];
            color1 = colors;
            color2 = colors;
            color3 = colors;
            color4 = colors;

            if (blk[0] != Blocks::GLOWSTONE && SmoothLighting) {
                color1 = (color1 + getBrightness(gx, gy + 1, gz - 1) + getBrightness(gx - 1, gy + 1, gz) +
                    getBrightness(gx - 1, gy + 1, gz - 1)) / 4.0;
                color2 = (color2 + getBrightness(gx, gy + 1, gz + 1) + getBrightness(gx - 1, gy + 1, gz) +
                    getBrightness(gx - 1, gy + 1, gz + 1)) / 4.0;
                color3 = (color3 + getBrightness(gx, gy + 1, gz + 1) + getBrightness(gx + 1, gy + 1, gz) +
                    getBrightness(gx + 1, gy + 1, gz + 1)) / 4.0;
                color4 = (color4 + getBrightness(gx, gy + 1, gz - 1) + getBrightness(gx + 1, gy + 1, gz) +
                    getBrightness(gx + 1, gy + 1, gz - 1)) / 4.0;
            }

            color1 /= BrightnessMax;
            color2 /= BrightnessMax;
            color3 /= BrightnessMax;
            color4 /= BrightnessMax;

            va.addPrimitive(4, {
                tcx + size, tcy + size, color1, color1, color1, -0.5f+ x, 0.5f+ y, -0.5f+ z, 4.0f,
                tcx + size, tcy + size, color2, color2, color2, -0.5f+ x, 0.5f+ y, 0.5f+ z, 4.0f,
                tcx + size, tcy + size, color3, color3, color3, 0.5f+ x, 0.5f+ y, 0.5f+ z, 4.0f,
                tcx + size, tcy + size, color4, color4, color4, 0.5f+ x, 0.5f+ y, -0.5f+ z, 4.0f
            });
        }

        tcx = Textures::getTexcoordX(blk[0], 3);
        tcy = Textures::getTexcoordY(blk[0], 3);

        // Bottom Face
        if (!(getBlockInfo(blk[6])
                .
                isOpaque() || (blk[6] == blk[0] &&
                    !getBlockInfo(blk[0]).isOpaque()
                )
            )
            ||
            blk[0] == Blocks::LEAF
        ) {
            colors = brt[6];
            color1 = colors;
            color2 = colors;
            color3 = colors;
            color4 = colors;

            if (blk[0] != Blocks::GLOWSTONE && SmoothLighting) {
                color1 = (colors + getBrightness(gx, gy - 1, gz - 1) + getBrightness(gx - 1, gy - 1, gz) +
                    getBrightness(gx - 1, gy - 1, gz - 1)) / 4.0;
                color2 = (colors + getBrightness(gx, gy - 1, gz - 1) + getBrightness(gx + 1, gy - 1, gz) +
                    getBrightness(gx + 1, gy - 1, gz - 1)) / 4.0;
                color3 = (colors + getBrightness(gx, gy - 1, gz + 1) + getBrightness(gx + 1, gy - 1, gz) +
                    getBrightness(gx + 1, gy - 1, gz + 1)) / 4.0;
                color4 = (colors + getBrightness(gx, gy - 1, gz + 1) + getBrightness(gx - 1, gy - 1, gz) +
                    getBrightness(gx - 1, gy - 1, gz + 1)) / 4.0;
            }

            color1 /= BrightnessMax;
            color2 /= BrightnessMax;
            color3 /= BrightnessMax;
            color4 /= BrightnessMax;

            va.addPrimitive(4, {
                tcx + size, tcy + size, color1, color1, color1, -0.5f+ x, -0.5f+ y, -0.5f+ z, 5.0f,
                tcx + size, tcy + size, color2, color2, color2, 0.5f+ x, -0.5f+ y, -0.5f+ z, 5.0f,
                tcx + size, tcy + size, color3, color3, color3, 0.5f+ x, -0.5f+ y, 0.5f+ z, 5.0f,
                tcx + size, tcy, color4, color4, color4, -0.5f+ x, -0.5f+ y, 0.5f+ z, 5.0f
            });
        }
    }


    void RenderChunk(Chunk* c) {
        int x, y, z;
        constexpr auto fmt = VertexFormat(2, 3, 0, 3, 1);
        va.setFormat(fmt);
        for (x = 0; x < 16; x++) {
            for (y = 0; y < 16; y++) {
                for (z = 0; z < 16; z++) {
                    const Block curr = c->getBlock(x, y, z);
                    if (curr == Blocks::AIR) continue;
                    if (!getBlockInfo(curr).isTranslucent()) renderblock(x, y, z, c);
                }
            }
        }
        c->vbo[0].update(va);
        for (x = 0; x < 16; x++) {
            for (y = 0; y < 16; y++) {
                for (z = 0; z < 16; z++) {
                    Block curr = c->getBlock(x, y, z);
                    if (curr == Blocks::AIR) continue;
                    if (getBlockInfo(curr).isTranslucent() && getBlockInfo(curr).isSolid()) renderblock(x, y, z, c);
                }
            }
        }
        c->vbo[1].update(va);
        for (x = 0; x < 16; x++) {
            for (y = 0; y < 16; y++) {
                for (z = 0; z < 16; z++) {
                    Block curr = c->getBlock(x, y, z);
                    if (curr == Blocks::AIR) continue;
                    if (!getBlockInfo(curr).isSolid()) renderblock(x, y, z, c);
                }
            }
        }
        c->vbo[2].update(va);
    }
}
