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
#include "Definitions.h"
#include "Hitbox.h"

namespace Particles {
    const int PARTICALE_max = 4096;

    struct Particle {
        bool exist = false;
        double xpos, ypos, zpos;
        float xsp, ysp, zsp, psize, tcX, tcY;
        int lasts;
        Hitbox::AABB hb;
    };

    extern std::vector<Particle> ptcs;
    extern int ptcsrendered;
    void update(Particle& ptc);
    void updateall();
    void render(Particle& ptc);
    void renderall(double xpos, double ypos, double zpos);
    void throwParticle(Block pt, float x, float y, float z, float xs, float ys, float zs, float psz, int last);
}
