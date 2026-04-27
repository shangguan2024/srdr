#include "FrameBuffer.hpp"
#include "Color.hpp"
#include "ColorAttachment.hpp"
#include <cstdint>

namespace srdr {

FrameBuffer::FrameBuffer(int width, int height, int colorAttachmentCount, bool hasDepth)
        : m_width(width),
          m_height(height),
          m_color_attachments(colorAttachmentCount, ColorAttachment(width, height)) {
    if (hasDepth) {
        enableDepth();
    }
}

void FrameBuffer::enableDepth() { m_depth_attachment.emplace(m_width, m_height); }

void FrameBuffer::writeColor(int index, int x, int y, const Color& color) {
    m_color_attachments[index].write(x, y, color.toUint32());
}

void FrameBuffer::writeColor(int index, int x, int y, uint32_t color) {
    m_color_attachments[index].write(x, y, color);
}

void FrameBuffer::writeDepth(int x, int y, float depth) { m_depth_attachment->write(x, y, depth); }

bool FrameBuffer::testDepth(int x, int y, float depth) const {
    return m_depth_attachment->test(x, y, depth);
}

bool FrameBuffer::testAndWriteDepth(int x, int y, float depth) {
    return m_depth_attachment->testAndWrite(x, y, depth);
}

Color FrameBuffer::getColor(int index, int x, int y) const {
    return Color(m_color_attachments[index].get(x, y));
}

float FrameBuffer::getDepth(int x, int y) const { return m_depth_attachment->get(x, y); }

void FrameBuffer::clearColor(int index) { m_color_attachments[index].clear(); }

void FrameBuffer::clearColor() {
    for (auto& color_attachment: m_color_attachments) {
        color_attachment.clear();
    }
}

void FrameBuffer::clearDepth() { m_depth_attachment->clear(); }

uint32_t* FrameBuffer::getColorAttachmentData(int index) {
    return m_color_attachments[index].data();
}

const uint32_t* FrameBuffer::getColorAttachmentData(int index) const {
    return m_color_attachments[index].data();
}

float* FrameBuffer::getDepthAttachmentData() { return m_depth_attachment->data(); }

const float* FrameBuffer::getDepthAttachmentData() const { return m_depth_attachment->data(); }

} // namespace srdr
