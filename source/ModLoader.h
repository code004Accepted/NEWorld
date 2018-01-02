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