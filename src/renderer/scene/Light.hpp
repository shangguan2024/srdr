#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Color.hpp"
#include "Vector.hpp"

namespace srdr {

struct DirectionalLight {
    Vec3 direction;
    Color color;
    float intensity;
};

struct PointLight {
    Vec3 position;
    Color color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    // TODO
};

} // namespace srdr

#endif // LIGHT_HPP
