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

//Object 所有生物、可移动物体、非静态方块的基类
class Object {
public:
    Object(double x, double y, double z) : _x(x), _y(y), _z(z), vtxs(0), VBO(0) { };

    virtual ~Object() { };
    virtual void render() const = 0;
    const double getXPos() const { return _x; }
    const double getYPos() const { return _y; }
    const double getZPos() const { return _z; }

protected:
    int _id;
    double _x, _y, _z; //位置
    vtxCount vtxs;
    VBOID VBO;
};
