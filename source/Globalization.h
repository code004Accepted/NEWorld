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