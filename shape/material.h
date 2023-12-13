#ifndef __MATERIAL__
#define __MATERIAL__
#include <limits>
#include <cmath>
#include <vector>
/**
 * @brief this is struct of shape.h material
 *
 * @param Vec2f &a (albedo) : specular reflection constant, diffuse reflection constant 
 * @param const Vec3f The direction of the ray line
 * @param float &t0 Length of ray line
 */
struct Material{
Material(const Vec2f &a, const Vec3f &color, const float &spec) : albedo(a), diffuse_color(color), specular_exponent(spec) {}
    Material() : albedo(1,0), diffuse_color(), specular_exponent() {} 
    Vec2f albedo;
    Vec3f diffuse_color;
    float specular_exponent;
};

#endif
