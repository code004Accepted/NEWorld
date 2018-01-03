#pragma once
#include <functional>
#include "ModSupport.h"

extern std::vector<Command> commands;

namespace Mod {

    extern std::map<std::string, void*> sharedData;

    APIPackage getPackage();
}