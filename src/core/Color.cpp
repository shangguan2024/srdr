#include "Color.hpp"
#include <cmath>
#include <cstdint>

namespace srdr {

Color::Color(float r, float g, float b)
        : data{ r, g, b, 1.0f } {}

Color::Color(float r, float g, float b, float a)
        : data{ r, g, b, a } {}

Color::Color(const Vec4f& color)
        : data(color.data) {}

Color Color::operator*(float value) const {
    return Color(r * value, g * value, b * value, a * value);
}

Color& Color::operator*=(float value) {
    r *= value;
    g *= value;
    b *= value;
    a *= value;
    return *this;
}

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

} // namespace srdr
