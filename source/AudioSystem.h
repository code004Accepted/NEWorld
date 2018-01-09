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
#include<AL/ALDevice.h>

namespace AudioSystem {
    extern ALDevice Device;
    //Gain
    extern ALfloat BGMGain; //背景音乐
    extern ALfloat SoundGain; //音效
    //Set
    extern ALenum DopplerModel; //设置OpenAL的距离模型
    extern ALfloat DopplerFactor; //多普勒因子
    extern ALfloat SpeedOfSound; //声速
    const ALfloat Air_SpeedOfSound = 343.3f;
    const ALfloat Water_SpeedOfSound = 1473.0f;
    //Update
    extern bool FallBefore; //OnGround
    extern bool DownWaterBefore; //InWater
    extern int BGMNum;
    //Buffer
    extern ALuint BGM[10];
    extern ALuint Run;
    extern ALuint Click;
    extern ALuint Fall;
    extern ALuint BlockClick;
    extern ALuint DownWater;
    //Source
    extern ALuint SBGM;
    extern ALuint SRun;
    extern ALuint SClick;
    extern ALuint SFall;
    extern ALuint SBlockClick;
    extern ALuint SDownWater;
    void Init();
    void Update(ALfloat PlayerPos[3], bool BFall, bool BBlockClick, ALfloat BlockPos[3], int Run, bool BDownWater);
    void ClickEvent();
    void UnInit();
}
