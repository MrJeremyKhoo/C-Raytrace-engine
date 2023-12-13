#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"
#include "light.h"
#include "shape/shape.h"

/**
 * @brief calcualtion of reflected ray using Snell's law
 * @param const Vec3f I: incident ray
 * @param const Vec3f N: normal of incidence
 */
Vec3f reflect(const Vec3f &I, const Vec3f &N) {
    return I - N*2.f*(I*N);
}
/**
 * @brief for each sphere, check if intersect, render the material of the closer sphere
 * @param const Vec3f orig: ray origin
 * @param const Vec3f dir: direction of ray
 * @param const Sphere sphere: sphere
 */
bool view_ray_intersect(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, Vec3f &hit, Vec3f &N, Material &material) {
    float spheres_dist = std::numeric_limits<float>::max();
    for(size_t i=0; i < spheres.size(); i++) {
        float t0;
        if(spheres[i].ray_intersect(orig, dir, t0) && t0 < spheres_dist) {
            spheres_dist = t0; //vector distance away from origin
            hit = orig + dir*t0; //vector incident on sphere
            N = (hit - spheres[i].center).normalize(); //normal of incident
            material = spheres[i].material;
        }
    }
    return spheres_dist < 1000;

}

/**
 * @brief change the colour of sphere if ray hits sphere
 * @param const Vec3f orig: ray origin
 * @param const Vec3f dir: direction of ray
 * @param const Sphere sphere: sphere
 */
Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, const std::vector<Light> &lights) {
    Vec3f hit, N;
    Material material;

    if (!view_ray_intersect(orig, dir, spheres, hit, N, material)) {
        return Vec3f(0.5, 0.8, 0.9); // background color
    }
    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for(size_t i=0; i< lights.size(); i++) {
        Vec3f light_dir = (lights[i].position - hit).normalize();
        float light_distance = (lights[i].position - hit).norm();

        Vec3f shadow_orig = light_dir*N < 0 ? hit - N*1e-3 : hit + N*1e-3; // checking if the point lies in the shadow of the lights[i]
        Vec3f shadow_pt, shadow_N;
        Material tmpmaterial;
        if (view_ray_intersect(shadow_orig, light_dir, spheres, shadow_pt, shadow_N, tmpmaterial) && (shadow_pt-shadow_orig).norm() < light_distance)
            continue;
        diffuse_light_intensity += lights[i].intensity * std::max(0.f,light_dir*N);
        specular_light_intensity += powf(std::max(0.f, reflect(light_dir, N)*dir), material.specular_exponent)*lights[i].intensity;
    }
    return material.diffuse_color * diffuse_light_intensity * material.albedo[1] + Vec3f(1., 1., 1.)*specular_light_intensity * material.albedo[0]; //from phong reflection model
}

/**
 * @brief choose to render a colour
 * @param sphere
 */
void render(const std::vector<Sphere> &spheres, const std::vector<Light> &lights) {
    const int width    = 1024;
    const int height   = 768;
    const int fov      = M_PI/2;
    std::vector<Vec3f> framebuffer(width*height);

    #pragma omp parallel for //run the following in parrallel
    for (size_t j = 0; j<height; j++) {
        for (size_t i = 0; i<width; i++) {
            framebuffer[i+j*width] = Vec3f(j/float(height),i/float(width), 0); //set default frame pictures
            float x =  (2*(i + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
            float y = -(2*(j + 0.5)/(float)height - 1)*tan(fov/2.);
            Vec3f dir = Vec3f(x, y, -1).normalize(); 
            framebuffer[i+j*width] = cast_ray(Vec3f(0,0,0), dir, spheres, lights);
        }
    }
  std::ofstream ofs; // save the framebuffer to file
    ofs.open("./out.ppm");
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (size_t i = 0; i < height*width; ++i) {
        Vec3f &c = framebuffer[i];
        float max = std::max(c[0], std::max(c[1], c[2]));
        if (max>1) c = c*(1./max);
        for (size_t j = 0; j<3; j++) {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }
    ofs.close();

}

int main() {
    Material blue(Vec2f(0.3,  0.6),Vec3f(0.2, 0.55, 0.91), 50);
    Material red(Vec2f(0.5,  1),Vec3f(0.3, 0.1, 0.1),50);
    Material green(Vec2f(0.3,  0.6),Vec3f(0.35, .8, 0.42),10);
    Material yellow(Vec2f(0.3,  0.6),Vec3f(0.76, 0.78, 0.31),10);

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Vec3f(-4, 0, -16), 2, yellow));
    spheres.push_back(Sphere(Vec3f(-2.5, -1, -12), 2, red));
    spheres.push_back(Sphere(Vec3f( 0, 0, -20), 3, green));
    spheres.push_back(Sphere(Vec3f( 3.5, 2.5, -15), 3.2, blue));
    std::vector<Light>  lights;
    lights.push_back(Light(Vec3f(-20, 20,  20), 1.5));
    lights.push_back(Light(Vec3f( 30, 50, -25), 1.8));
    lights.push_back(Light(Vec3f( 30, 20,  30), 1.7));
    render(spheres, lights);
    return 0;
}
