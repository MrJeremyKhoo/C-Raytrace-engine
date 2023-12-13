#ifndef __LIGHT__
#define __LIGHT__
#include <limits>
#include <cmath>
#include <vector>

struct Light {
    Light(const Vec3f &p, const float &i) : position(p), intensity(i) {}
    Vec3f position;
    float intensity;
};

#endif
