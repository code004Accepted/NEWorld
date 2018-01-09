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
#define NEWORLD_USE_WINAPI
#define _USE_MATH_DEFINES

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cassert>
#include <math.h>
#include <memory>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

//GLFW
#define GLFW_DLL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef _MSC_VER
#include <filesystem>
namespace filesystem = std::experimental::filesystem;
#elif defined(__APPLE__)
#include <boost/filesystem>
namespace filesystem = boost::filesystem;
#else
#include <filesystem>
namespace filesystem = std::filesystem;
#endif
