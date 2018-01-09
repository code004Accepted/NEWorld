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
#include <string>
#include <vector>
#include "ModLoader.h"
#include "ModSupport.h"

namespace Mod {
    class ModLoader {
    public:
        static std::vector<ModInfo> mods;
        static void loadMods();
        static void unloadMods();

    private:
        enum ModLoadStatus { Success, MissDependence, InitFailed };

        static ModLoadStatus loadSingleMod(const std::string& modPath);

        typedef void* ModCall;
        typedef FARPROC FuncPtr;
        static ModCall loadMod(const std::string& filename);
        static FuncPtr getFunction(ModCall call, const std::string& functionName);
        static void unloadMod(ModCall call);
    };
}
