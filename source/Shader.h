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

#include <set>
#include <string>

class Shader {
public:
    Shader(const std::string& vshPath, const std::string& fshPath, bool bindLocation = false) :
        Shader(vshPath, fshPath, bindLocation, std::set<std::string>()) { }

    Shader(const std::string& vshPath, const std::string& fshPath, bool bindLocation, std::set<std::string> defines);

    void bind() {
        glUseProgramObjectARB(shaderProgram);
    }

    static void unbind() {
        glUseProgramObjectARB(0);
    }

    void release();

    bool setUniform(const char* uniform, float value);
    bool setUniform(const char* uniform, int value);
    bool setUniform(const char* uniform, float v0, float v1, float v2, float v3);
    bool setUniform(const char* uniform, float* value);

private:
    GLhandleARB loadShader(const std::string& filename, unsigned int mode, std::set<std::string> defines);
    void checkErrors(GLhandleARB res, int status, const std::string& errorMessage);

    GLhandleARB shaderFragment;
    GLhandleARB shaderVertex;
    GLhandleARB shaderProgram;
};
