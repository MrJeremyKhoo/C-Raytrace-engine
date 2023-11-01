#ifndef__GEOMETRY_H__ 
#define __GEOMETRY_H__
#include <cmath>
#include <vector>
#include<cassert>
#include <iostream>

//make vector struct, bounds checking...
template <size_t LENGTH, typename T> struct vec {
    vec() { for (size_t i=LENGTH; i--; data_[i] = T()); } //T() is default constructor for state type T
          T& operator[](const size_t i)       { assert(i<LENGTH); return data_[i]; } //overoad of operator function of array primitive
    const T& operator[](const size_t i) const { assert(i<LENGTH); return data_[i]; }
private:
    T data_[LENGTH];
};

typedef vec<2, float> Vec2f;
typedef vec<3,float> Vec3f;
typedef vec<3, int> Vec3i;
typedef vec<4,float> Vec4f;
//define a few primitives for convenience

//to define generic class for non-float classes 
template <typename T> struct vec<2,T> {
    vec(): x(T()), y(T()) {}
    vec(T X, T Y): x(X), y(Y) {}
    template <class U> vec<2,T>(const vec<2,U> &v);
        T& operator[](const size_t i) {assert(i<2); return i<=0 ? x:y; }
        const T& operator[](const size_t i) const {assert(i<2); return i<=0 ? x:y; }
    T x,y;
};

#endif //GEOMETRY_H__
