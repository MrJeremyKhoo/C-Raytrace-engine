/**
 * @file geometry.h
 * @brief defines vector struct
 *
 * Vector with bounds checking
 * Vector with dot product/element checking
 */

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include <cmath>
#include <cassert>
/**
 * @brief A template structure representing a vector with a fixed dimension.
 *
 * This structure provides basic operations for working with vectors of fixed dimension.
 * Override the array operator to do bounds checking
 *
 * @tparam DIM The dimension of the vector.
 * @tparam T   The type of elements in the vector.
 */
template <size_t DIM, typename T> struct vec {
    vec() { for (size_t i=DIM; i--; data_[i] = T()); }
          T& operator[](const size_t i)       { assert(i<DIM); return data_[i]; }
    const T& operator[](const size_t i) const { assert(i<DIM); return data_[i]; }
private:
    T data_[DIM];
};

/**
 * @brief A template structure for vector of 3 dimentions
 *
 * This structure provides basic operations for working with vectors of fixed dimension.
 * Override the array operator to do bounds checking
 * Provide Eudcledian norm function and normalize function
 * @tparam DIM The dimension of the vector.
 * @tparam T   The type of elements in the vector.
 */
template <typename T> struct vec<3,T> {
    vec() : x(T()), y(T()), z(T()) {}
    vec(T X, T Y, T Z) : x(X), y(Y), z(Z) {}
          T& operator[](const size_t i)       { assert(i<3); return i<=0 ? x : (1==i ? y : z); }
    const T& operator[](const size_t i) const { assert(i<3); return i<=0 ? x : (1==i ? y : z); }
    float norm() const { return std::sqrt(x*x+y*y+z*z); }
    vec<3,T> & normalize(T l=1) { *this = (*this)*(l/norm()); return *this; }
    T x,y,z;
};

/**
 * @brief operator overload to do element-wise multiplication
 * @tparam 1st dimentional vector
 * @tparam 2nd dimentional vector
 */
template<size_t DIM,typename T> T operator*(const vec<DIM,T>& lhs, const vec<DIM,T>& rhs) {
    T ret = T();
    for (size_t i=DIM; i--; ret+=lhs[i]*rhs[i]);
    return ret;
}

/**
 * @brief operator overload to do element-wise addition
 * @tparam 1st dimentional vector
 * @tparam 2nd dimentional vector
 */
template<size_t DIM,typename T>vec<DIM,T> operator+(vec<DIM,T> lhs, const vec<DIM,T>& rhs) {
    for (size_t i=DIM; i--; lhs[i]+=rhs[i]);
    return lhs;
}

/**
 * @brief operator overload to do element-wise subtraction
 * @tparam 1st dimentional vector
 * @tparam 2nd dimentional vector
 */
template<size_t DIM,typename T>vec<DIM,T> operator-(vec<DIM,T> lhs, const vec<DIM,T>& rhs) {
    for (size_t i=DIM; i--; lhs[i]-=rhs[i]);
    return lhs;
}

/**
 * @brief operator overload to do element-wise addition to a constant
 * @tparam 1st dimentional vector
 * @tparam const number
 */
template<size_t DIM,typename T,typename U> vec<DIM,T> operator*(const vec<DIM,T> &lhs, const U& rhs) {
    vec<DIM,T> ret;
    for (size_t i=DIM; i--; ret[i]=lhs[i]*rhs);
    return ret;
}

/**
 * @brief inverse the vector
 * @tparam a dimentional vector
 */
template<size_t DIM,typename T> vec<DIM,T> operator-(const vec<DIM,T> &lhs) {
    return lhs*T(-1);
}

typedef vec<3, float> Vec3f;

#endif //__GEOMETRY_H__
