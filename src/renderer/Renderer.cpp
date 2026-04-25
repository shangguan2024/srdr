#include "Renderer.hpp"
#include "FrameBuffer.hpp"
#include "IWindow.hpp"
#include "VertexLoader.hpp"
#include "VertexShader.hpp"
#include <memory>
#include <utility>

namespace srdr {

Renderer::Renderer(std::shared_ptr<IWindow> window)
        : m_window(std::move(window)) {
    init();
}

void Renderer::beginScene() {
    m_vertex_buffer.clear();
    m_index_buffer.clear();
    m_vertex_input_cache.clear();
    m_vertex_output_cache.clear();
}

void Renderer::endScene() { render(); }

void Renderer::render() {
    m_vertex_loader->loadVertex(m_vertex_buffer, m_index_buffer, m_vertex_input_cache);
    m_vertex_shader->processVertices(m_vertex_input_cache, m_vertex_output_cache);

    // TODO
}

void Renderer::init() {
    m_vertex_loader = std::make_unique<VertexLoader>();
    m_vertex_shader = std::make_unique<VertexShader>();

    // TODO

    auto [window_width, window_height] = m_window->getWindowSize();
    m_frame_buffer = std::make_unique<FrameBuffer>(window_width, window_height);
}

} // namespace srdr
