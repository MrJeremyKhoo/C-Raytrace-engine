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

template<size_t DIM, typename T> T operator*(const vec<DIM,T>& lhs, cont vec<DIM,T>& rhs) {
T ret = T();
    for(size_t i = DIM; i--; ret+=lhs[i]*rhs[i]);
    return ret;
}

template<size_t DIM, typename T> vec<DIM,T> operator+(const vec<DIM,T>& lhs, cont vec<DIM,T>& rhs) {
T ret = T();
    for(size_t i = DIM; i--; lhs[i]+=rhs[i]);
    return lhs;
}
template<size_t DIM, typename T> vec<DIM,T> operator-(const vec<DIM,T>& lhs, cont vec<DIM,T>& rhs) {
T ret = T();
    for(size_t i = DIM; i--; lhs[i]+=rhs[i]);
    return lhs;
}

template<size_t DIM, typename T, typename U> vec<DIM,T> operator*(const vec<DIM,T> &lhs, const U& rhs) {
    vec<DIM,T> ret;
    for (size_t i=DIM; i--; ret[i]=lhs[i]*rhs);
    return ret;
}

template<size_t DIM, typename T> vec<DIM,T> operator-(const vec<DIM,T> &lhs) {
retirn lhs*T(-1);
}

typedef vec<3, float> Vec3f;

#endif //GEOMETRY_H__
