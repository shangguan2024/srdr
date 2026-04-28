#ifndef COLOR_HPP
#define COLOR_HPP

#include "Vector.hpp"
#include <array>
#include <cstdint>

namespace srdr {

struct Color {
    Color() = default;
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
    Color(const Vec4f& color);
    Color(const Vec3f& rgb, float a);
    Color(uint32_t argb);

    // clang-format off
    union {
        struct { float r, g, b, a; };
        std::array<float, 4> data;
    };
    // clang-format on

    Color& operator*=(float value);

    Vec3 rgb() const;

    uint8_t red() const;
    uint8_t green() const;
    uint8_t blue() const;
    uint8_t alpha() const;

    // Returns a 4 byte value equal to #AARRGGBB
    uint32_t toUint32() const;
};

Color operator+(const Color& c1, const Color& c2);

Color operator*(const Color& color, float value);

} // namespace srdr

#endif // COLOR_HPP
