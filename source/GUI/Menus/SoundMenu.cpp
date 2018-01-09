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

#include "Menus.h"

namespace Menus {
    class SoundMenu : public GUI::Form {
    private:
        GUI::label title;
        GUI::button backbtn;
        GUI::trackbar Musicbar, SoundBar;

        void onLoad() override {
            title = GUI::label(GetStrbyKey("NEWorld.Sound.caption"), -225, 225, 20, 36, 0.5, 0.5, 0.0, 0.0);
            Musicbar = GUI::trackbar(GetStrbyKey("NEWorld.Sound.MusicGain"), 100, AudioSystem::BGMGain * 300, -200, 201,
                                     60, 84, 0.5, 0.5, 0.0, 0.0);
            SoundBar = GUI::trackbar(GetStrbyKey("NEWorld.Sound.SoundGain"), 100, AudioSystem::SoundGain * 300, -200,
                                     201, 90, 114, 0.5, 0.5, 0.0, 0.0);
            backbtn = GUI::button(GetStrbyKey("NEWorld.render.back"), -250, 250, -44, -20, 0.5, 0.5, 1.0, 1.0);
            registerControls(4, &title, &Musicbar, &SoundBar, &backbtn);
        }

        void onUpdate() override {
            char text[100];
            AudioSystem::BGMGain = float(Musicbar.barpos) / 300.0f;
            AudioSystem::SoundGain = float(SoundBar.barpos) / 300.0f;
            sprintf_s(text, ":%d%%", Musicbar.barpos / 3);
            Musicbar.text = GetStrbyKey("NEWorld.Sound.MusicGain") + text;
            sprintf_s(text, ":%d%%", SoundBar.barpos / 3);
            SoundBar.text = GetStrbyKey("NEWorld.Sound.SoundGain") + text;
            AudioSystem::SpeedOfSound = AudioSystem::Air_SpeedOfSound;
            EFX::EAXprop = Generic;
            EFX::UpdateEAXprop();
            float Pos[] = {0.0f, 0.0f, 0.0f};
            AudioSystem::Update(Pos, false, false, Pos, false, false);
            if (backbtn.clicked) GUI::PopPage();
        }
    };

    void Soundmenu() { PushPage(new SoundMenu); }
}
