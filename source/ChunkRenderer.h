// 
// NEWorld: ChunkRenderer.h
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
#include "Definitions.h"
#include "Blocks.h"
#include "Textures.h"

namespace World {
    class Chunk;
}

namespace ChunkRenderer {
    const int delta[6][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};

    //合并面的一整个面 | One face in merge face
    struct QuadPrimitive {
        int x, y, z, length, direction;
        /*
        * 如果顶点颜色不同（平滑光照启用时），这个方形就不能和别的方形拼合起来。
        * 这个变量同时意味着四个顶点颜色是否不同。
        * If the vertexes have different colors (smoothed lighting), the primitive cannot connect with others.
        * This variable also means whether the vertexes have different colors.
        */
        bool once;
        //顶点颜色 | Vertex colors
        int col0, col1, col2, col3;
        //纹理ID | Texture ID
        TextureID tex;

        QuadPrimitive() : x(0), y(0), z(0), length(0), direction(0), once(false),
                          col0(0), col1(0), col2(0), col3(0), tex(Textures::NULLBLOCK) { }
    };

    //深度模型的面 | Face in depth model
    struct QuadPrimitiveDepth {
        int x, y, z, length, direction;

        QuadPrimitiveDepth() : x(0), y(0), z(0), length(0), direction(0) { }
    };

    void renderPrimitive(QuadPrimitive& p);
    void RenderPrimitive_Depth(QuadPrimitiveDepth& p);
    void RenderChunk(World::Chunk* c);
    void MergeFaceRender(World::Chunk* c);
    void RenderDepthModel(World::Chunk* c);
}
