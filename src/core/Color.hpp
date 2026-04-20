#ifndef COLOR_HPP
#define COLOR_HPP

#include "Vector.hpp"
#include <cstdint>

namespace srdr {

class Color {
public:
    Color() = default;

    uint8_t red() const;
    uint8_t green() const;
    uint8_t blue() const;
    uint8_t alpha() const;

    // Returns a 4 byte value equal to #AARRGGBB
    uint32_t toUint32() const;

private:
    Vec4f m_data;
};

} // namespace srdr

#endif // COLOR_HPP
