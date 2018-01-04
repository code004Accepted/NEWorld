#pragma once

namespace Hitbox {
    //Axis Aligned Bounding Box
    struct AABB{
        double xmin, ymin, zmin;
        double xmax, ymax, zmax;
    };

    bool inXclip(const AABB& boxA, const AABB& boxB);
    bool inYclip(const AABB& boxA, const AABB& boxB);
    bool inZclip(const AABB& boxA, const AABB& boxB);

    bool Hit(const AABB& boxA, const AABB& boxB);

    double maxMoveOnXclip(const AABB& boxA, const AABB& boxB, double movedist);
    double maxMoveOnYclip(const AABB& boxA, const AABB& boxB, double movedist);
    double maxMoveOnZclip(const AABB& boxA, const AABB& boxB, double movedist);

    AABB Expand(const AABB& box, double xe, double ye, double ze);
    void Move(AABB &box, double xa, double ya, double za);
    void MoveTo(AABB &box, double x, double y, double z);
}