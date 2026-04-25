#include "DepthAttachment.hpp"
#include <algorithm>

namespace srdr {

DepthAttachment::DepthAttachment(int width, int height)
        : m_width(width),
          m_height(height),
          m_depths(width * height, 1.0f) {}

void DepthAttachment::write(int x, int y, float depth) {
    if (isValidCoord(x, y)) {
        m_depths[x + y * m_width] = depth;
    }
}

bool DepthAttachment::test(int x, int y, float depth) const {
    if (isValidCoord(x, y)) {
        return depth < m_depths[x + y * m_width];
    }
    return false;
}

bool DepthAttachment::testAndWrite(int x, int y, float depth) {
    if (isValidCoord(x, y)) {
        int index = x + y * m_width;
        if (depth < m_depths[index]) {
            m_depths[index] = depth;
            return true;
        }
    }
    return false;
}

void DepthAttachment::clear() { std::ranges::fill(m_depths, 1.0f); }

float* DepthAttachment::data() { return m_depths.data(); }

const float* DepthAttachment::data() const { return m_depths.data(); }

[[nodiscard]] bool DepthAttachment::isValidCoord(int x, int y) const noexcept {
    return 0 <= x && x < m_width && 0 <= y && y < m_height;
}

} // namespace srdr
