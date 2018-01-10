// 
// NEWorld: Globalization.cpp
// NEWorld: A Free Game with Similar Rules to Minecraft.
// Copyright (C) 2015-2018 NEWorld Team
// 
// NEWorld is free software: you can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or 
// (at your option) any later version.
// 
// NEWorld is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General 
// Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with NEWorld.  If not, see <http://www.gnu.org/licenses/>.
// 

#include "Globalization.h"
#include <fstream>

namespace Globalization {
    int count;
    std::string Cur_Lang = "zh_CN", Cur_Symbol = "", Cur_Name = "";
    std::map<int, Line> Lines;
    std::map<std::string, int> keys;

    bool LoadLang(const std::string& lang) {
        std::ifstream f("Lang/" + lang + ".lang");
        if (f.bad()) {
            exit(-101);
            return false;
        }
        Lines.clear();
        Cur_Lang = lang;
        f >> Cur_Symbol;
        f.get();
        std::getline(f, Cur_Name);
        for (int i = 0; i < count; i++) { std::getline(f, Lines[i].str); }
        f.close();
        return true;
    }

    bool Load() {
        std::ifstream f("Lang/Keys.lk");
        if (f.bad()) return false;
        f >> count;
        f.get();
        for (int i = 0; i < count; i++) {
            std::string temp;
            std::getline(f, temp);
            keys[temp] = i;
        }
        f.close();
        return LoadLang(Cur_Lang);
    }

    std::string GetStrbyid(int id) { return Lines[id].str; }

    std::string GetStrbyKey(const std::string& key) { return Lines[keys[key]].str; }
}
