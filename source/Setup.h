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

struct GLFWwindow;

void splashScreen();

void createWindow();

void setupScreen();

void setupNormalFog();

void loadTextures();

void WindowSizeFunc(GLFWwindow* win, int width, int height);

void MouseButtonFunc(GLFWwindow*, int button, int action, int);

void CharInputFunc(GLFWwindow*, unsigned int c);

void MouseScrollFunc(GLFWwindow*, double, double yoffset);
