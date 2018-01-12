// 
// NEWorld: FunctionsKit.cpp
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

#include "FunctionsKit.h"

unsigned int g_seed;

// Codecvt Functionality 
namespace {
    // utility wrapper to adapt locale-bound facets for wstring/wbuffer convert
    template <class Facet>
    struct DeletableFacet : Facet {
        template <class ...Args>
        explicit DeletableFacet(Args&& ...args) : Facet(std::forward<Args>(args)...) {}
    };

    DeletableFacet<std::codecvt<char16_t, char, std::mbstate_t>> cvt;
}

unsigned int MByteToWChar(char16_t* dst, const char* src, unsigned int n) {
    const char* fromNext;
    char16_t* toNext;
    std::mbstate_t mb = std::mbstate_t();
    if (cvt.in(mb, src, src + n, fromNext, dst, dst + n, toNext) == std::codecvt_base::error)
        throw std::runtime_error("Codecvt Failure");
    return toNext - dst;
}

unsigned int WCharToMByte(char* dst, const char16_t* src, unsigned int n) {
    const char16_t* fromNext;
    char* toNext;
    std::mbstate_t mb = std::mbstate_t();
    if (cvt.out(mb, src, src + n, fromNext, dst, dst + n, toNext) == std::codecvt_base::error)
        throw std::runtime_error("Codecvt Failure");
    return toNext - dst;
}

std::vector<std::string> split(const std::string& str, const std::string& pattern) {
    std::vector<std::string> ret;
    if (pattern.empty()) return ret;
    size_t start = 0, index = str.find_first_of(pattern, 0);
    while (index != std::string::npos) {
        if (start != index)
            ret.push_back(str.substr(start, index - start));
        start = index + 1;
        index = str.find_first_of(pattern, start);
    }
    if (!str.substr(start).empty())
        ret.push_back(str.substr(start));
    return ret;
}
