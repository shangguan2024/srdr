#ifndef FRAGMENT_HPP
#define FRAGMENT_HPP

#include "Color.hpp"
#include "Vector.hpp"

namespace srdr {

struct FragmentInput {
    Vec4 f_position;
    Vec3 v_normal;
    Color v_color;
    Vec2 v_uv;
    Vec4 v_world_position;
};

struct FragmentOutput {
    Vec3 o_position;
    Color o_color;
};

} // namespace srdr

#endif // FRAGMENT_HPP
