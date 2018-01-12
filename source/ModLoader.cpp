// 
// NEWorld: ModLoader.cpp
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

#include "ModLoader.h"
#include <Windows.h>
#include <functional>
#include <iostream>
#include "API.h"

std::vector<ModInfo> Mod::ModLoader::mods;

//查找一个文件夹下所有的子目录
std::vector<std::string> findFolders(const std::string& path) {
    std::vector<std::string> ret;
    for (auto&& x : filesystem::directory_iterator(path))
        if (is_directory(x.path()))
            ret.push_back(x.path().string());
    return ret;
}

void Mod::ModLoader::loadMods() {
    std::vector<std::string> modLoadList = findFolders("Mods/"); //获得Mods/下所有的文件夹
    bool successAtLeastOne = false;
    do {
        //循环加载Mod，直到某一次循环一个成功加载的都没有为止（因为依赖项）
        successAtLeastOne = false;
        for (std::vector<std::string>::iterator iter = modLoadList.begin(); iter != modLoadList.end();) {
            ModLoadStatus status = loadSingleMod("Mods/" + *iter + "/entry.dll");
            if (status == Success) successAtLeastOne = true;
            if (status != MissDependence) iter = modLoadList.erase(iter); //只要不是因缺少依赖而失败就删掉记录
            else ++iter;
        }
    }
    while (successAtLeastOne);
    std::cout << "[Console][Game]Load complete! "
        << mods.size() << " mod" << (mods.size() > 1 ? "s" : "") << " loaded." << std::endl;
}

//加载单个Mod，loadMods会调用该函数
Mod::ModLoader::ModLoadStatus Mod::ModLoader::loadSingleMod(const std::string& modPath) {
    ModCall call = loadMod(modPath);
    ModInfo (*getModInfo)() = reinterpret_cast<ModInfo(*)()>(getFunction(call, "getModInfo"));
    bool (*init)(APIPackage) = reinterpret_cast<bool(*)(APIPackage)>(getFunction(call, "init"));
    ModInfo info = getModInfo(); //获得Mod信息
    std::cout << "[Console][Game]Loading Mod " << info.name << "[" << info.version << "]" << std::endl;
    if (strcmp(info.dependence, "") != 0) {
        //判断并检查依赖项
        bool foundDependence = false;
        for (auto& mod : mods) {
            if (mod.name == info.dependence) {
                foundDependence = true;
                break;
            }
        }
        if (!foundDependence) return MissDependence;
    }
    if (!(*init)(getPackage())) return InitFailed; //初始化Mod
    info.call = call;
    mods.push_back(info);
    return Success;
}

void Mod::ModLoader::unloadMods() {
    for (size_t i = 0; i != mods.size(); i++) { unloadMod(mods[i].call); }
    mods.clear();
}


Mod::ModLoader::ModCall Mod::ModLoader::loadMod(const std::string& filename) { return LoadLibrary(filename.c_str()); }

Mod::ModLoader::FuncPtr Mod::ModLoader::getFunction(ModCall call, const std::string& functionName) {
    return reinterpret_cast<FuncPtr>(GetProcAddress(static_cast<HMODULE>(call), functionName.c_str()));
}

void Mod::ModLoader::unloadMod(ModCall call) { FreeLibrary(static_cast<HMODULE>(call)); }
