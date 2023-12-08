#ifndef __SHAPE_H__
#define __SHAPE_H__
#include <limits>
#include <cmath>
#include <vector>
#include "../geometry.h"
#include "shape.h"

struct Sphere {
    Vec3f center;
    float radius;

    Sphere(const Vec3f &c, const float &r): center(c), radius(r) {}

    /**
     * @brief Calculate where the ray intersect the spheere
     *
     * @tparam const Vec3f &orig the origin of ray line
     * @tparam const Vec3f The direction of the ray line
     * @tparam float &t0 Length of ray line
     */
    bool ray_intersect(const Vec3f &orig, const Vec3f &dir, float &t0) const {
        Vec3f L = center - orig;
        float tca = L * dir;
        float d2 = L*L - tca*tca;
        if(d2 > radius*radius) return false;
        float thc = sqrtf(radius*radius - d2);
        t0 = tca -thc;
        float t1 = tca + thc;
        if(t0 < 0){t0 = t1;return false;}
        return true;
    }

};

#endif //__SHAPE_H__
