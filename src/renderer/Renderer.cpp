#include "Renderer.hpp"
#include "FrameBuffer.hpp"
#include "IWindow.hpp"
#include <memory>
#include <utility>

namespace srdr {

Renderer::Renderer(std::shared_ptr<IWindow> window)
        : m_window(std::move(window)) {
    init();
}

void Renderer::render() {
    // TODO

    m_window->drawFrame(m_frame_buffer->data());
}

void Renderer::init() {
    auto [window_width, window_height] = m_window->getWindowSize();

    // TODO

    m_frame_buffer = std::make_unique<FrameBuffer>(window_width, window_height);
}

} // namespace srdr
