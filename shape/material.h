#ifndef __MATERIAL__
#define __MATERIAL__
#include <limits>
#include <cmath>
#include <vector>

struct Material {
    Material(const Vec3f &color) : diffuse_color(color) {}
    Material(): diffuse_color() {}
    Vec3f diffuse_color;
};
#endif
