#ifndef FRAME_BUFFER_HPP
#define FRAME_BUFFER_HPP

#include "Color.hpp"
#include "ColorAttachment.hpp"
#include "DepthAttachment.hpp"
#include <cstdint>
#include <optional>
#include <vector>

namespace srdr {

class FrameBuffer {
public:
    FrameBuffer(int width, int height, int colorAttachmentCount = 1, bool hasDepth = true);

    void enableDepth();

    void writeColor(int index, int x, int y, const Color& color);
    void writeColor(int index, int x, int y, uint32_t color);

    void writeDepth(int x, int y, float depth);
    bool testDepth(int x, int y, float depth) const;
    bool testAndWriteDepth(int x, int y, float depth);

    Color getColor(int index, int x, int y) const;

    float getDepth(int x, int y) const;

    void clearColor(int index);
    void clearColor();

    void clearDepth();
    uint32_t* getColorAttachmentData(int index);
    const uint32_t* getColorAttachmentData(int index) const;

    float* getDepthAttachmentData();
    const float* getDepthAttachmentData() const;

private:
    int m_width, m_height;

    std::vector<ColorAttachment> m_color_attachments;
    std::optional<DepthAttachment> m_depth_attachment;
};

} // namespace srdr

#endif // FRAME_BUFFER_HPP
