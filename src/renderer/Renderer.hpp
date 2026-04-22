#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "FrameBuffer.hpp"
#include "IWindow.hpp"
#include "OutputMerger.hpp"
#include "PixelShader.hpp"
#include "PrimitiveAssembler.hpp"
#include "Rasterizer.hpp"
#include "VertexLoader.hpp"
#include "VertexShader.hpp"
#include <memory>

namespace srdr {

class Renderer {
public:
    explicit Renderer(std::shared_ptr<IWindow> window);

    void render();

private:
    void init();

    std::shared_ptr<IWindow> m_window;

    std::unique_ptr<VertexLoader> m_vertex_loader;
    std::unique_ptr<VertexShader> m_vertex_shader;
    std::unique_ptr<PrimitiveAssembler> m_primitive_assembler;
    std::unique_ptr<Rasterizer> m_rasterizer;
    std::unique_ptr<PixelShader> m_pixel_shader;
    std::unique_ptr<OutputMerger> m_output_merger;
    std::unique_ptr<FrameBuffer> m_frame_buffer;
};

} // namespace srdr

#endif // RENDERER_HPP
