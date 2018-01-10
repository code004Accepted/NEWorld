// 
// NEWorld: Renderer.h
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
#include "Frustum.h"
#include "Shader.h"

namespace Renderer {
    //我猜你肯定不敢看Renderer.cpp  --qiaozhanrong
    //猜对了  --Null

    enum {
        MainShader,
        MergeFaceShader,
        ShadowShader,
        DepthShader
    };

    const int ArraySize = 2621440;
    extern float* VA;
    extern int size;
    extern int Vertexes;
    extern bool AdvancedRender;
    extern int ShadowRes;
    extern int maxShadowDist;
    extern int shadowdist;
    extern float sunlightXrot, sunlightYrot;
    extern unsigned int DepthTexture;
    extern std::vector<Shader> shaders;
    extern int ActiveShader;

    void Flush(VBOID& buffer, vtxCount& vtxs);
    void renderbuffer(VBOID buffer, vtxCount vtxs, int tc, int cc, int ac = 0);

    void initShaders();

    inline void bindShader(int shaderID) {
        shaders[shaderID].bind();
        ActiveShader = shaderID;
    }

    void destroyShaders();
    void EnableShaders();
    void DisableShaders();
    void StartShadowPass();
    void EndShadowPass();

    using VertexBufferID = GLuint;

    class VertexFormat {
    public:
        // Vertex attribute count
        size_t textureCount, colorCount, normalCount, coordinateCount;
        // Vertex attributes count (sum of all)
        int vertexAttributeCount;

        VertexFormat() : textureCount(0), colorCount(0), normalCount(0), coordinateCount(0), vertexAttributeCount(0) {}

        VertexFormat(int textureElementCount, int colorElementCount, int normalElementCount, int coordinateElementCount)
            : textureCount(textureElementCount), colorCount(colorElementCount), normalCount(normalElementCount), coordinateCount(coordinateElementCount),
            vertexAttributeCount(textureElementCount + colorElementCount + normalElementCount + coordinateElementCount) {
        }
    };

    class VertexArray {
    public:
        VertexArray(int maxVertexes, const VertexFormat& format) :
            mMaxVertexes(maxVertexes), mVertexes(0), mFormat(format),
            mData(std::make_unique<float[]>(mMaxVertexes * format.vertexAttributeCount)),
            mVertexAttributes(std::make_unique<float[]>(format.vertexAttributeCount)) {}
        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;
        VertexArray(VertexArray&&) = delete;
        VertexArray& operator=(VertexArray&&) = delete;
        ~VertexArray() = default;

        void clear() noexcept {  mVertexes = 0; }

        // Set texture coordinates
        void setTexture(std::initializer_list<float> texture) noexcept {
            std::copy(texture.begin(), texture.end(), mVertexAttributes.get());
        }

        // Set color value
        void setColor(std::initializer_list<float> color) noexcept {
            std::copy(color.begin(), color.end(), mVertexAttributes.get() + mFormat.textureCount);
        }

        // Set normal vector
        void setNormal(std::initializer_list<float> normal) noexcept {
            std::copy(normal.begin(), normal.end(), mVertexAttributes.get() + mFormat.textureCount + mFormat.colorCount);
        }

        // Add vertex
        void addVertex(const float* coords) noexcept {
            auto cnt = mFormat.textureCount + mFormat.colorCount + mFormat.normalCount;
            memcpy(mData.get() + mVertexes * mFormat.vertexAttributeCount, mVertexAttributes.get(), cnt * sizeof(float));
            memcpy(mData.get() + mVertexes * mFormat.vertexAttributeCount + cnt, coords, mFormat.coordinateCount * sizeof(float));
            mVertexes++;
        }

        void addVertex(std::initializer_list<float> coords) noexcept {
            addVertex(coords.begin());
        }

        void addPrimitive(size_t size, std::initializer_list<float> d) noexcept {
            std::fill(d.begin(), d.end(), mData.get() + mVertexes * mFormat.vertexAttributeCount);
            mVertexes += size;
        }

        // Get current vertex format
        const VertexFormat& getFormat() const noexcept { return mFormat; }

        // Get current vertex data
        const float* getData() const noexcept { return mData.get(); }

        // Get current vertex count
        size_t getVertexCount() const noexcept { return mVertexes; }

        // Set current vertex format
        void setFormat(const VertexFormat& format) {
            mVertexes = 0; mFormat = format;
            mData = std::make_unique<float[]>(mMaxVertexes * format.vertexAttributeCount);
            mVertexAttributes = std::make_unique<float[]>(format.vertexAttributeCount);
        }

    private:
        // Max vertex count
        const size_t mMaxVertexes;
        // Vertex count
        size_t mVertexes;
        // Vertex array format
        VertexFormat mFormat;
        // Vertex array
        std::unique_ptr<float[]> mData;
        // Current vertex attributes
        std::unique_ptr<float[]> mVertexAttributes;
    };

    class VertexBuffer {
    public:
        VertexBuffer() : id(0), vertexes(0) {}

        VertexBuffer(VertexBufferID id_, int vertexes_, const VertexFormat& format_) :
            id(id_), vertexes(vertexes_), format(format_) {}

        VertexBuffer(VertexBuffer&& rhs) noexcept :
            id(rhs.id), vertexes(rhs.vertexes), format(rhs.format) {
            rhs.vertexes = rhs.id = 0;
            rhs.format = VertexFormat();
        }

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        explicit VertexBuffer(const VertexArray& va);

        VertexBuffer& operator=(VertexBuffer&& rhs) noexcept {
            id = rhs.id; vertexes = rhs.vertexes; format = rhs.format;
            rhs.vertexes = rhs.id = 0;
            rhs.format = VertexFormat();
            return *this;
        }

        ~VertexBuffer() {
            destroy();
        }

        // upload new data
        void update(const VertexArray& va);

        // Render vertex buffer
        void render() const;

        // Destroy vertex buffer
        void destroy() {
            if (id) {
                glDeleteBuffersARB(1, &id);
                vertexes = id = 0;
                format = VertexFormat();
            }
        }

        bool isEmpty() const noexcept {
            return (vertexes == 0);
        }

    private:
        // Buffer ID
        VertexBufferID id;
        // Vertex count
        int vertexes;
        // Buffer format
        VertexFormat format;
    };

}
