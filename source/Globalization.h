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

#include <map>
#include <string>

namespace Globalization {
    struct Line {
        std::string str;
        int id;
    };

    extern int count;
    extern std::map<int, Line> Lines;
    extern std::map<std::string, int> keys;
    extern std::string Cur_Lang;

    bool LoadLang(const std::string& lang);
    bool Load();
    std::string GetStrbyid(int id);
    std::string GetStrbyKey(const std::string& key);
}
