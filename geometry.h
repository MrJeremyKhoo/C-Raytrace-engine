#infdef__GEOMETRY_H__ 
#define __GEOMETRY_H__
#include <cmath>
#include <vector>
#include<cassert>
#include <iostream>

//we make vector struct for speed
template <size_t LENGTH, typename T> struct vec {
    vec() { for (size_t i=LENGTH; i--; data_[i] = T()); }
          T& operator[](const size_t i)       { assert(i<LENGTH); return data_[i]; }
    const T& operator[](const size_t i) const { assert(i<LENGTH); return data_[i]; }
private:
    T data_[LENGTH];
};





#endif //GEOMETRY_H__