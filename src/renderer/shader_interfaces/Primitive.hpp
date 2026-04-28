#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "Geometry.hpp"
#include "Vertex.hpp"
#include <array>

namespace srdr {

struct EdgeEquation : public PlaneEquation {
    EdgeEquation() = default;
    EdgeEquation(float A, float B, float C)
            : PlaneEquation(A, B, C) {}
};

struct Primitive {
    std::array<ScreenVertex, 3> vertices;

    AABB<int, 2> aabb;

    float area;

    std::array<EdgeEquation, 3> edges;

    PlaneEquation depth_plane;
    PlaneEquation inv_w_plane;
    std::array<PlaneEquation, 4> rgba_plane;
    std::array<PlaneEquation, 3> normal_plane;
    std::array<PlaneEquation, 2> uv_plane;
    std::array<PlaneEquation, 4> world_pos_plane;
};

} // namespace srdr

#endif // PRIMITIVE_HPP
