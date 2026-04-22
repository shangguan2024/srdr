#include "FrameBuffer.hpp"
#include <cstdint>

namespace srdr {

FrameBuffer::FrameBuffer(int width, int height)
        : m_width(width),
          m_height(height),
          m_pixels(width * height) {}

void FrameBuffer::putPixel(int x, int y, const Color& color) {
    if (0 <= x && x < m_width && 0 <= y && y < m_height) {
        m_pixels[x + y * m_width] = color.toUint32();
    }
}

uint32_t* FrameBuffer::data() { return m_pixels.data(); }

const uint32_t* FrameBuffer::data() const { return m_pixels.data(); }

} // namespace srdr
