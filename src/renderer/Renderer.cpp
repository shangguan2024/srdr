#include "Renderer.hpp"
#include "FragmentShader.hpp"
#include "FrameBuffer.hpp"
#include "IWindow.hpp"
#include "PrimitiveAssembler.hpp"
#include "Rasterizer.hpp"
#include "VertexLoader.hpp"
#include "VertexShader.hpp"
#include <memory>
#include <utility>

namespace srdr {

Renderer::Renderer(std::shared_ptr<IWindow> window)
        : m_window(std::move(window)),
          m_clip_vertex_cache(m_vertex_output_cache) {
    init();
}

void Renderer::beginScene() {
    m_vertex_buffer.clear();
    m_index_buffer.clear();
    m_vertex_input_cache.clear();
    m_vertex_output_cache.clear();
    m_primitive_cache.clear();
    m_fragment_input_cache.clear();
    m_fragment_output_cache.clear();
}

void Renderer::endScene() { render(); }

void Renderer::draw(const std::vector<Vertex>& vertices, const std::vector<std::size_t>& indices) {
    draw(vertices.data(), 0, vertices.size(), indices.data(), 0, indices.size(), 0ull);
}

void Renderer::draw(const Vertex* vertices, int v_base, int v_count, const std::size_t* indices,
        int i_base, int i_count, std::size_t base_diff) {
    std::size_t base = m_vertex_buffer.size();
    for (int i = 0; i < v_count; ++i) {
        m_vertex_buffer.emplace_back(vertices[v_base + i]);
    }
    for (int i = 0; i < i_count; ++i) {
        m_index_buffer.emplace_back(indices[i_base + i] - base_diff + base);
    }
}

void Renderer::render() {
    m_vertex_loader->loadVertex(m_vertex_buffer, m_index_buffer, m_vertex_input_cache);
    m_vertex_shader->processVertices(m_vertex_input_cache, m_vertex_output_cache);
    m_primitive_assembler->setWindowSize(m_window->getWindowSize());
    m_primitive_assembler->assemblePrimitives(m_clip_vertex_cache, m_primitive_cache);
    m_rasterizer->setWindowSize(m_window->getWindowSize());
    m_rasterizer->rasterizePrimitives(m_primitive_cache, m_fragment_input_cache);
    m_fragment_shader->processFragments(m_fragment_input_cache, m_fragment_output_cache);

    // TODO
}

void Renderer::init() {
    m_vertex_loader = std::make_unique<VertexLoader>();
    m_vertex_shader = std::make_unique<VertexShader>();
    m_primitive_assembler = std::make_unique<PrimitiveAssembler>();
    m_rasterizer = std::make_unique<Rasterizer>();
    m_fragment_shader = std::make_unique<FragmentShader>();

    // TODO

    auto [window_width, window_height] = m_window->getWindowSize();
    m_frame_buffer = std::make_unique<FrameBuffer>(window_width, window_height);
}

} // namespace srdr
