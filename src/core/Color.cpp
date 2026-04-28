#include "Color.hpp"
#include <cmath>
#include <cstdint>

namespace srdr {

Color::Color(float r, float g, float b)
        : data{ r, g, b, 1.0f } {}

Color::Color(float r, float g, float b, float a)
        : data{ r, g, b, a } {}

Color::Color(const Vec3f& rgb, float a)
        : r(rgb.r),
          g(rgb.g),
          b(rgb.b),
          a(a) {}

Color::Color(const Vec4f& color)
        : data(color.data) {}

Color::Color(uint32_t argb) {
    constexpr float denom = 1.0f / 255;
    b = ((uint8_t*) (&argb))[0] * denom;
    g = ((uint8_t*) (&argb))[1] * denom;
    r = ((uint8_t*) (&argb))[2] * denom;
    a = ((uint8_t*) (&argb))[3] * denom;
}

Color& Color::operator*=(float value) {
    r *= value;
    g *= value;
    b *= value;
    a *= value;
    return *this;
}

Vec3 Color::rgb() const { return Vec3(r, g, b); }

uint8_t Color::red() const { return uint8_t(std::round(r * 255)); }

uint8_t Color::green() const { return uint8_t(std::round(g * 255)); }

uint8_t Color::blue() const { return uint8_t(std::round(b * 255)); }

uint8_t Color::alpha() const { return uint8_t(a * 255); }

uint32_t Color::toUint32() const {
    uint32_t val;
    ((uint8_t*) (&val))[3] = alpha();
    ((uint8_t*) (&val))[2] = red();
    ((uint8_t*) (&val))[1] = green();
    ((uint8_t*) (&val))[0] = blue();
    return val;
}

Color operator+(const Color& c1, const Color& c2) {
    return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a);
}

Color operator*(const Color& color, float value) {
    return Color(color.r * value, color.g * value, color.b * value, color.a * value);
}

} // namespace srdr
