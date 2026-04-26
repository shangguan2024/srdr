#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <cstddef>

namespace srdr {

// f(x,y) = A*x + B*y + C
struct PlaneEquation {
    PlaneEquation() = default;
    PlaneEquation(float A, float B, float C);
    PlaneEquation(float x0, float y0, float f0, float x1, float y1, float f1, float x2, float y2,
            float f2);

    float A, B, C;

    static PlaneEquation computePlane(float x0, float y0, float f0, float x1, float y1, float f1,
            float x2, float y2, float f2);

    float stepX() const;
    float stepY() const;

    float evaluate(float x, float y) const;
};

template<typename T, std::size_t N>
struct AABB {};

template<typename T>
struct AABB<T, 2> {
    AABB() = default;

    T min_x, max_x;
    T min_y, max_y;
};

template<typename T>
struct AABB<T, 3> {
    AABB() = default;

    T min_x, max_x;
    T min_y, max_y;
    T min_z, max_z;
};

} // namespace srdr

#endif // GEOMETRY_HPP
