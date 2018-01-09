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
//#define NEWORLD_DEBUG
#ifndef NEWORLD_DEBUG
#pragma comment(linker, "/SUBSYSTEM:\"WINDOWS\" /ENTRY:\"mainCRTStartup\"")
#endif
//#define NEWORLD_SECURE
#include "StdInclude.h"
#include "Typedefs.h"
#include "FunctionsKit.h"

//Global Vars
const unsigned int VERSION = 39;
const std::string MAJOR_VERSION = "Alpha 0.";
const std::string minOR_VERSION = "5";
const std::string EXT_VERSION = " Technical Perview";
const int defaultwindowwidth = 852; //默认窗口宽度
const int defaultwindowheight = 480; //默认窗口高度
const int networkRequestFrequency = 3; //请求频率
const int networkRequestmax = 20; //理想最大请求队列长度
extern float FOVyNormal;
extern float mousemove;
extern int viewdistance;
extern int cloudwidth;
extern int selectPrecision;
extern int selectDistance;
extern float walkspeed;
extern float runspeed;
extern int maxAirJumps;
extern bool SmoothLighting;
extern bool NiceGrass;
extern bool MergeFace;
extern bool GUIScreenBlur;
extern bool ppistretch;
extern int linelength;
extern int linedist;
extern float skycolorR;
extern float skycolorG;
extern float skycolorB;
extern float FOVyRunning;
extern float FOVyExt;
extern int Multisample;
extern bool vsync;
extern double stretch;
extern int gametime;
const int gameTimemax = 43200;
//extern float daylight;

extern int windowwidth;
extern int windowheight;
extern bool gamebegin, gameexit, bagOpened;

extern TextureID BlockTextures, BlockTextures3D;
extern TextureID tex_select, tex_unselect, tex_title, tex_mainmenu[6];
extern TextureID DestroyImage[11];
extern TextureID DefaultSkin;

extern bool multiplayer;
extern std::string serverip;
extern unsigned short port;

extern Mutex_t Mutex;
extern Thread_t updateThread;
extern double lastupdate, updateTimer;
extern double lastframe;
extern bool updateThreadRun, updateThreadPaused;

extern bool mpclient, mpserver;
extern bool shouldGetScreenshot;
extern bool shouldGetThumbnail;
extern bool FirstUpdateThisFrame;
extern bool FirstFrameThisUpdate;
extern double SpeedupAnimTimer;
extern double TouchdownAnimTimer;
extern double screenshotAnimTimer;
extern double bagAnimTimer;
extern double bagAnimDuration;

extern int GLVersionMajor, GLVersionMinor, GLVersionRev;
extern GLFWwindow* MainWindow;
extern GLFWcursor* MouseCursor;
extern double mx, my, mxl, myl;
extern int mw, mb, mbp, mbl, mwl;
extern double mxdelta, mydelta;
extern std::string inputstr;
void AppCleanUp();
