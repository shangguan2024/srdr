#ifndef FRAME_BUFFER_HPP
#define FRAME_BUFFER_HPP

#include "Color.hpp"
#include <cstdint>
#include <vector>

namespace srdr {

class FrameBuffer {
public:
    FrameBuffer() = default;
    FrameBuffer(int width, int height);

    void putPixel(int x, int y, const Color& color);

private:
    int m_width, m_height;
    std::vector<uint32_t> m_pixels;
};

} // namespace srdr

#endif // FRAME_BUFFER_HPP
