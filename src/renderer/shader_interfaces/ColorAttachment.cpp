#include "ColorAttachment.hpp"
#include <algorithm>
#include <cstdint>

namespace srdr {

ColorAttachment::ColorAttachment(int width, int height)
        : m_width(width),
          m_height(height),
          m_colors(width * height) {}

void ColorAttachment::write(int x, int y, uint32_t color) {
    if (isValidCoord(x, y)) {
        m_colors[x + y * m_width] = color;
    }
}

void ColorAttachment::clear() { std::ranges::fill(m_colors, 0u); }

uint32_t* ColorAttachment::data() { return m_colors.data(); }

const uint32_t* ColorAttachment::data() const { return m_colors.data(); }

[[nodiscard]] bool ColorAttachment::isValidCoord(int x, int y) const noexcept {
    return 0 <= x && x < m_width && 0 <= y && y < m_height;
}

} // namespace srdr
