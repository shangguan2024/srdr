#include "Color.hpp"
#include <cmath>
#include <cstdint>

namespace srdr {

uint8_t Color::red() const { return uint8_t(std::round(m_data[0] * 255)); }

uint8_t Color::green() const { return uint8_t(std::round(m_data[1] * 255)); }

uint8_t Color::blue() const { return uint8_t(std::round(m_data[2] * 255)); }

uint8_t Color::alpha() const { return uint8_t(m_data[3] * 255); }

uint32_t Color::toUint32() const {
    uint32_t val;
    ((uint8_t*) (&val))[3] = alpha();
    ((uint8_t*) (&val))[2] = red();
    ((uint8_t*) (&val))[1] = green();
    ((uint8_t*) (&val))[0] = blue();
    return val;
}

} // namespace srdr
