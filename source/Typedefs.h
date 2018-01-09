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
//Types/constants define
#include <cstdint>
#include <thread>
#include <mutex>
typedef unsigned char blockprop;
typedef unsigned char Brightness;
typedef unsigned int TextureID;
typedef unsigned short Block;
typedef unsigned short item;
typedef unsigned int VBOID;
typedef int vtxCount;
typedef int SkinID;
typedef uint64_t ChunkID;
typedef unsigned int onlineid;
typedef std::mutex* Mutex_t;
typedef std::thread* Thread_t;
typedef unsigned int (*ThreadFunc_t)(void* param);
#define ThreadFunc unsigned int
