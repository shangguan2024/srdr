#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Color.hpp"
#include "Vector.hpp"

namespace srdr {

struct Vertex {
    Vec3 position;
    Vec3 normal;
    Color color;
    Vec2 uv;
};

struct VertexInput {
    Vec3 a_position;
    Vec3 a_normal;
    Color a_color;
    Vec2 a_uv;
};

struct VertexOutput {
    Vec4 v_position;
    Vec3 v_normal;
    Color v_color;
    Vec2 v_uv;
};

} // namespace srdr

#endif // VERTEX_HPP
