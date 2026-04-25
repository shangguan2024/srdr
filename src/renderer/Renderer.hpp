#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "FrameBuffer.hpp"
#include "IWindow.hpp"
#include "OutputMerger.hpp"
#include "PixelShader.hpp"
#include "PrimitiveAssembler.hpp"
#include "Rasterizer.hpp"
#include "Vertex.hpp"
#include "VertexLoader.hpp"
#include "VertexShader.hpp"
#include <cstddef>
#include <memory>
#include <vector>

namespace srdr {

class Renderer {
public:
    Renderer(std::shared_ptr<IWindow> window);

    void beginScene();
    void endScene();

private:
    void init();

    void render();

    std::shared_ptr<IWindow> m_window;

    std::unique_ptr<VertexLoader> m_vertex_loader;
    std::unique_ptr<VertexShader> m_vertex_shader;
    std::unique_ptr<PrimitiveAssembler> m_primitive_assembler;
    std::unique_ptr<Rasterizer> m_rasterizer;
    std::unique_ptr<PixelShader> m_pixel_shader;
    std::unique_ptr<OutputMerger> m_output_merger;

    std::vector<Vertex> m_vertex_buffer;
    std::vector<std::size_t> m_index_buffer;
    std::vector<VertexInput> m_vertex_input_cache;
    std::vector<VertexOutput> m_vertex_output_cache;
    std::unique_ptr<FrameBuffer> m_frame_buffer;
};

} // namespace srdr

#endif // RENDERER_HPP
