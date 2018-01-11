// 
// NEWorld: Renderer.cpp
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

#include "Renderer.h"
#include "Shader.h"
#include <algorithm>
#include "World.h"

namespace Renderer {
    /*
    好纠结啊好纠结，“高级”渲染模式里的所有数据要不要都用VertexAttribArray啊。。。
    然而我还是比较懒。。。所以除了【附加】的顶点属性之外，其他属性（比如颜色、纹理坐标）都保留原来的算了。。。
    
    说到为啥要用【附加】的顶点属性。。。这是由于Shadow Map的精度问题。。。
    有的时候背光面的外圈会有亮光。。。很难看。。。所以要用Shader把背光面弄暗。。。
    于是如何让shader知道这个面朝哪里呢？懒得用NormalArray的我就用了一个附加的顶点属性。。。
    0.0f表示前面(z+)，1.0f表示后面(z-)，2.0f表示右面(x+)，3.0f表示左面(x-)，4.0f表示上面(y+)，5.0f表示下面(y-)

        你没有看错。。。这些值。。。全都是

            浮！
                点！
                    型！
                        的！！！！！！！

    坑爹的GLSL不支持整型作为顶点属性。。。只好用浮点型代替了(╯‵□′)╯︵┻━┻
    然后为了解决浮点数的精度问题，我在shader里写了个四舍五入取整。。。
    不说了。。。

    等等我还没有签名呢。。。
    --qiaozhanrong

    ====================================================
    留言板：

    1楼. qiaozhanrong: 自己抢个沙发先
    2楼. Null: 这就是你在源码里写这么一长串的理由？23333333333
    3楼. qiaozhanrong: 无聊啊233333333333

    4楼. [请输入姓名]: [请输入回复内容]

    [回复]
    ====================================================
    */
    bool AdvancedRender;
    int ShadowRes = 4096;
    int maxShadowDist = 4;
    int shadowdist;
    float sunlightXrot, sunlightYrot;
    std::vector<Shader> shaders;
    int ActiveShader;
    int index = 0, size = 0;
    unsigned int ShadowFBO, DepthTexture;
    unsigned int ShaderAttribLoc = 0;

    void initShaders() {
        ShaderAttribLoc = 1;
        std::set<std::string> defines;
        defines.insert("MergeFace");

        sunlightXrot = 30.0f;
        sunlightYrot = 60.0f;
        shadowdist = std::min(maxShadowDist, viewdistance);
        shaders.reserve(4);
        shaders.emplace_back("Shaders/Main.vsh", "Shaders/Main.fsh", true);
        shaders.emplace_back("Shaders/Main.vsh", "Shaders/Main.fsh", true, defines);
        shaders.emplace_back("Shaders/Shadow.vsh", "Shaders/Shadow.fsh", false);
        shaders.emplace_back("Shaders/Depth.vsh", "Shaders/Depth.fsh", false, defines);

        glGenTextures(1, &DepthTexture);
        glBindTexture(GL_TEXTURE_2D, DepthTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, ShadowRes, ShadowRes, 0, GL_DEPTH_COMPONENT,
                     GL_UNSIGNED_INT, nullptr);

        glActiveTextureARB(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, DepthTexture);
        glActiveTextureARB(GL_TEXTURE0);

        glGenFramebuffersEXT(1, &ShadowFBO);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, ShadowFBO);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, DepthTexture, 0);
        if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT) {
            DebugError("Frame buffer creation error!");
        }
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

        for (int i = 0; i < 2; i++) {
            shaders[i].bind();
            if (i == 0) shaders[i].setUniform("Tex", 0);
            else shaders[i].setUniform("Tex3D", 0);
            shaders[i].setUniform("DepthTex", 1);
            shaders[i].setUniform("SkyColor", skycolorR, skycolorG, skycolorB, 1.0f);
        }
        Shader::unbind();
    }

    void destroyShaders() {
        for (size_t i = 0; i != shaders.size(); i++)
            shaders[i].release();
        shaders.clear();
        glDeleteTextures(1, &DepthTexture);
        glDeleteFramebuffersEXT(1, &ShadowFBO);
    }

    void EnableShaders() {
        shadowdist = std::min(maxShadowDist, viewdistance);

        //Enable shader
        Shader& shader = shaders[MergeFace ? MergeFaceShader : MainShader];
        bindShader(MergeFace ? MergeFaceShader : MainShader);

        //Calc matrix
        float scale = 16.0f * sqrt(3.0f);
        float length = shadowdist * scale;
        Frustum frus;
        frus.loadIdentity();
        frus.setOrtho(-length, length, -length, length, -length, length);
        frus.multRotate(sunlightXrot, 1.0f, 0.0f, 0.0f);
        frus.multRotate(sunlightYrot, 0.0f, 1.0f, 0.0f);

        //Set uniform
        shader.setUniform("renderdist", viewdistance * 16.0f);
        shader.setUniform("Depth_proj", frus.getProjMatrix());
        shader.setUniform("Depth_modl", frus.getModlMatrix());

        //Enable arrays for additional vertex attributes
        glEnableVertexAttribArrayARB(ShaderAttribLoc);
    }

    void DisableShaders() {
        //Disable shader
        Shader::unbind();

        //Disable arrays for additional vertex attributes
        glDisableVertexAttribArrayARB(ShaderAttribLoc);
    }

    void StartShadowPass() {
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, ShadowFBO);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        bindShader(ShadowShader);
        glViewport(0, 0, ShadowRes, ShadowRes);
    }

    void EndShadowPass() {
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        glDrawBuffer(GL_BACK);
        glReadBuffer(GL_BACK);
        Shader::unbind();
        glViewport(0, 0, windowwidth, windowheight);
    }


    void VertexBuffer::update(const VertexArray& va) {
        vertexes = va.getVertexCount();
        format = va.getFormat();
        if (vertexes == 0)
            destroy();
        else {
            if (id == 0)
                glGenBuffersARB(1, &id);
            glBindBufferARB(GL_ARRAY_BUFFER_ARB, id);
            glBufferDataARB(GL_ARRAY_BUFFER_ARB, va.getVertexCount() * sizeof(float) *
                            format.vertexAttributeCount,
                            va.getData(), GL_STATIC_DRAW_ARB);
        }
    }

    VertexBuffer::VertexBuffer(const VertexArray& va)
        : VertexBuffer() { update(va); }

    void VertexBuffer::render() const {
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, id);
        if (format.textureCount != 0) {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(
                format.textureCount, GL_FLOAT,
                format.vertexAttributeCount * sizeof(float),
                nullptr
            );
        }
        if (format.colorCount != 0) {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(
                format.colorCount, GL_FLOAT,
                format.vertexAttributeCount * sizeof(float),
                reinterpret_cast<float*>(format.textureCount * sizeof(float))
            );
        }
        if (format.normalCount != 0) {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(
                /*format.normalCount,*/ GL_FLOAT,
                                        format.vertexAttributeCount * sizeof(float),
                                        reinterpret_cast<float*>((format.textureCount + format.colorCount) * sizeof(
                                            float))
            );
        }
        if (format.coordinateCount != 0) {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(
                format.coordinateCount, GL_FLOAT,
                format.vertexAttributeCount * sizeof(float),
                reinterpret_cast<float*>((format.textureCount + format.colorCount + format.normalCount) * sizeof(float))
            );
        }

        glDrawArrays(GL_QUADS, 0, vertexes);

        if (format.textureCount)
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        if (format.colorCount)
            glDisableClientState(GL_COLOR_ARRAY);
        if (format.normalCount)
            glDisableClientState(GL_NORMAL_ARRAY);
        if (format.coordinateCount)
            glDisableClientState(GL_VERTEX_ARRAY);

    }


    void VertexBuffer::destroy() {
        if (id) {
            World::vbuffersShouldDelete.push_back(id);
            vertexes = id = 0;
        }
    }

}
