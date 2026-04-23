#include "DepthBuffer.hpp"

namespace srdr {

DepthBuffer::DepthBuffer(int width, int height)
        : m_width(width),
          m_height(height),
          m_depths(width * height, 1.0f) {}

void DepthBuffer::update(int x, int y, float depth) {
    if (isValidCoord(x, y)) {
        m_depths[x + y * m_width] = depth;
    }
}

bool DepthBuffer::test(int x, int y, float z) const {
    if (isValidCoord(x, y)) {
        return z < m_depths[x + y * m_width];
    }
    return false;
}

bool DepthBuffer::testAndUpdate(int x, int y, float z) {
    if (isValidCoord(x, y)) {
        int index = x + y * m_width;
        if (z < m_depths[index]) {
            m_depths[index] = z;
            return true;
        }
    }
    return false;
}

float* DepthBuffer::data() { return m_depths.data(); }

const float* DepthBuffer::data() const { return m_depths.data(); }

[[nodiscard]] bool DepthBuffer::isValidCoord(int x, int y) const noexcept {
    return 0 <= x && x < m_width && 0 <= y && y < m_height;
}

} // namespace srdr
