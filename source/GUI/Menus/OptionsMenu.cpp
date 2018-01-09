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

void saveOptions();

namespace Menus {
    class OptionsMenu : public GUI::Form {
    private:
        GUI::label title;
        GUI::trackbar FOVyBar, mmsBar, viewdistBar;
        GUI::button rdstbtn, langbtn, gistbtn, backbtn, savebtn, sounbtn;
        //GUI::button rdstbtn, gistbtn, backbtn, savebtn;
        void onLoad() override {
            title = GUI::label(GetStrbyKey("NEWorld.options.caption"), -225, 225, 20, 36, 0.5, 0.5, 0.0, 0.0);
            FOVyBar = GUI::trackbar("", 120, (int)(FOVyNormal - 1), -250, -10, 60, 84, 0.5, 0.5, 0.0, 0.0);
            mmsBar = GUI::trackbar("", 120, (int)(mousemove * 40 * 2 - 1), 10, 250, 60, 84, 0.5, 0.5, 0.0, 0.0);
            viewdistBar = GUI::trackbar("", 120, (viewdistance - 2) * 4 - 1, -250, -10, 96, 120, 0.5, 0.5, 0.0, 0.0);
            rdstbtn = GUI::button(GetStrbyKey("NEWorld.options.rendermenu"), -250, -10, 204, 228, 0.5, 0.5, 0.0, 0.0);
            gistbtn = GUI::button(GetStrbyKey("NEWorld.options.guimenu"), 10, 250, 204, 228, 0.5, 0.5, 0.0, 0.0);
            langbtn = GUI::button(GetStrbyKey("NEWorld.options.languagemenu"), -250, -10, 240, 264, 0.5, 0.5, 0.0, 0.0);
            sounbtn = GUI::button(GetStrbyKey("NEWorld.options.soundmenu"), 10, 250, 240, 264, 0.5, 0.5, 0.0, 0.0);
            backbtn = GUI::button(GetStrbyKey("NEWorld.options.back"), -250, -10, -44, -20, 0.5, 0.5, 1.0, 1.0);
            savebtn = GUI::button(GetStrbyKey("NEWorld.options.save"), 10, 250, -44, -20, 0.5, 0.5, 1.0, 1.0);
            registerControls(10, &title, &FOVyBar, &mmsBar, &viewdistBar, &rdstbtn, &gistbtn, &backbtn, &savebtn,
                             &langbtn, &sounbtn);
            //registerControls(8, &title, &FOVyBar, &mmsBar, &viewdistBar, &rdstbtn, &gistbtn, &backbtn, &savebtn);
        }

        void onUpdate() override {
            FOVyNormal = (float)(FOVyBar.barpos + 1);
            mousemove = (mmsBar.barpos / 2 + 1) / 40.0f;
            viewdistance = (viewdistBar.barpos + 1) / 4 + 2;
            if (rdstbtn.clicked) Renderoptions();
            if (gistbtn.clicked) GUIoptions();
            if (backbtn.clicked) GUI::PopPage();
            if (savebtn.clicked) saveOptions();
            if (langbtn.clicked) {
                languagemenu();
                title.text = GetStrbyKey("NEWorld.options.caption");
                rdstbtn.text = GetStrbyKey("NEWorld.options.rendermenu");
                gistbtn.text = GetStrbyKey("NEWorld.options.guimenu");
                langbtn.text = GetStrbyKey("NEWorld.options.languagemenu");
                backbtn.text = GetStrbyKey("NEWorld.options.back");
                savebtn.text = GetStrbyKey("NEWorld.options.save");
            }
            if (sounbtn.clicked)Soundmenu();

            AudioSystem::SpeedOfSound = AudioSystem::Air_SpeedOfSound;
            EFX::EAXprop = Generic;
            EFX::UpdateEAXprop();
            float Pos[] = {0.0f, 0.0f, 0.0f};
            AudioSystem::Update(Pos, false, false, Pos, false, false);
            FOVyBar.text = strWithVar(GetStrbyKey("NEWorld.options.fov"), FOVyNormal);
            mmsBar.text = strWithVar(GetStrbyKey("NEWorld.options.sensitivity"), mousemove);
            viewdistBar.text = strWithVar(GetStrbyKey("NEWorld.options.distance"), viewdistance);
        }
    };

    void options() { PushPage(new OptionsMenu); }
}
