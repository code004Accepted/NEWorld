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
#include <ft2build.h>
#include FT_FREETYPE_H

namespace TextRenderer {
    struct UnicodeChar {
        bool aval;
        unsigned int tex;
        unsigned int buffer;
        unsigned int vtxs;
        int xpos, ypos;
        int width, height, advance;

        UnicodeChar() : aval(false), tex(0), buffer(0),
                        vtxs(0), xpos(0), ypos(0),
                        width(0), height(0), advance(0) { }
    };

    extern FT_Library library;
    extern FT_Face fontface;
    extern FT_GlyphSlot slot;
    extern UnicodeChar chars[65536];

    extern unsigned int gbe;
    extern unsigned int Font;
    extern int gloop;
    extern int ww, wh;
    extern float r, g, b, a;
    extern unsigned int unicodeTex[256];
    extern bool unicodeTexAval[256];
    extern bool useUnicodeASCIIFont;

    void BuildFont(int w, int h);
    void resize();
    void setFontColor(float r, float g, float b, float a);
    void loadchar(unsigned int uc);
    int getStrWidth(const std::string& s);
    void renderString(int x, int y, const std::string& glstring);
    void renderASCIIString(int x, int y, const std::string& glstring);
}
