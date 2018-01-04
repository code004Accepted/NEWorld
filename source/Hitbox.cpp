#include "Hitbox.h"
#include <algorithm>

namespace Hitbox {

    bool inXclip(const AABB& boxA, const AABB& boxB) {
        if (boxA.xmin > boxB.xmin && boxA.xmin < boxB.xmax || boxA.xmax > boxB.xmin && boxA.xmax < boxB.xmax) return true;
        if (boxB.xmin > boxA.xmin && boxB.xmin < boxA.xmax || boxB.xmax > boxA.xmin && boxB.xmax < boxA.xmax) return true;
        return false;
    }

    bool inYclip(const AABB& boxA, const AABB& boxB) {
        if (boxA.ymin > boxB.ymin && boxA.ymin < boxB.ymax || boxA.ymax > boxB.ymin && boxA.ymax < boxB.ymax) return true;
        if (boxB.ymin > boxA.ymin && boxB.ymin < boxA.ymax || boxB.ymax > boxA.ymin && boxB.ymax < boxA.ymax) return true;
        return false;
    }

    bool inZclip(const AABB& boxA, const AABB& boxB) {
        if (boxA.zmin > boxB.zmin && boxA.zmin < boxB.zmax || boxA.zmax > boxB.zmin && boxA.zmax < boxB.zmax) return true;
        if (boxB.zmin > boxA.zmin && boxB.zmin < boxA.zmax || boxB.zmax > boxA.zmin && boxB.zmax < boxA.zmax) return true;
        return false;
    }

    bool Hit(const AABB& boxA, const AABB& boxB) {
        return inXclip(boxA, boxB) && inYclip(boxA, boxB) && inZclip(boxA, boxB);
    }

    double maxMoveOnXclip(const AABB& boxA, const AABB& boxB, double movedist) {
        //用boxA去撞boxB，别搞反了
        if (!(inYclip(boxA, boxB) && inZclip(boxA, boxB))) return movedist;
        else if (boxA.xmin >= boxB.xmax && movedist < 0.0) return std::max(boxB.xmax - boxA.xmin, movedist);
        else if (boxA.xmax <= boxB.xmin && movedist > 0.0) return std::min(boxB.xmin - boxA.xmax, movedist);
        return movedist;
    }

    double maxMoveOnYclip(const AABB& boxA, const AABB& boxB, double movedist) {
        //用boxA去撞boxB，别搞反了 （这好像是句废话）
        if (!(inXclip(boxA, boxB) && inZclip(boxA, boxB))) return movedist;
        else if (boxA.ymin >= boxB.ymax && movedist < 0.0) return std::max(boxB.ymax - boxA.ymin, movedist);
        else if (boxA.ymax <= boxB.ymin && movedist > 0.0) return std::min(boxB.ymin - boxA.ymax, movedist);
        return movedist;
    }

    double maxMoveOnZclip(const AABB& boxA, const AABB& boxB, double movedist) {
        //用boxA去撞boxB，别搞反了 （这好像还是句废话）
        if (!(inXclip(boxA, boxB) && inYclip(boxA, boxB))) return movedist;
        else if (boxA.zmin >= boxB.zmax && movedist < 0.0) return std::max(boxB.zmax - boxA.zmin, movedist);
        else if (boxA.zmax <= boxB.zmin && movedist > 0.0) return std::min(boxB.zmin - boxA.zmax, movedist);
        return movedist;
    }

    AABB Expand(const AABB& box, double xe, double ye, double ze) {
        AABB ret = box;
        if (xe > 0.0) ret.xmax += xe; else ret.xmin += xe;
        if (ye > 0.0) ret.ymax += ye; else ret.ymin += ye;
        if (ze > 0.0) ret.zmax += ze; else ret.zmin += ze;
        return ret;
    }

    void Move(AABB &box, double xa, double ya, double za) {
        box.xmin += xa; box.ymin += ya; box.zmin += za;
        box.xmax += xa; box.ymax += ya; box.zmax += za;
    }

    void MoveTo(AABB &box, double x, double y, double z) {
        double l, w, h;
        //注意在执行这个过程时，参数中的xyz坐标将成为移动后的AABB的中心，而不是初始化AABB时的原点！
        l = (box.xmax - box.xmin) / 2;
        w = (box.ymax - box.ymin) / 2;
        h = (box.zmax - box.zmin) / 2;
        box.xmin = x - l; box.ymin = y - w; box.zmin = z - h;
        box.xmax = x + l; box.ymax = y + w; box.zmax = z + h;
    }

}