#ifndef COLOR_HPP
#define COLOR_HPP

#include "Vector.hpp"

namespace srdr {

class Color {
public:
    Color() = default;

private:
    Vec4f m_data;
};

} // namespace srdr

#endif // COLOR_HPP
