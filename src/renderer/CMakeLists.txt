set(
SRDR_RENDERER_HEADERS
    shader_interfaces/FrameBuffer.hpp
    VertexLoader.hpp
    VertexShader.hpp
    PrimitiveAssembler.hpp
    Rasterizer.hpp
    PixelShader.hpp
    OutputMerger.hpp
    Renderer.hpp
)

set(
SRDR_RENDERER_SOURCES
    shader_interfaces/FrameBuffer.cpp
    VertexLoader.cpp
    VertexShader.cpp
    PrimitiveAssembler.cpp
    Rasterizer.cpp
    PixelShader.cpp
    OutputMerger.cpp
    Renderer.cpp
)

add_library(
srdr_renderer
STATIC
    ${SRDR_RENDERER_HEADERS}
    ${SRDR_RENDERER_SOURCES}
)

target_include_directories(
srdr_renderer
PUBLIC
    ${SRDR_RENDERER_INCLUDES}
    ${SRDR_CORE_INCLUDES}
PRIVATE
    ${SRDR_PLATFORM_INCLUDES}
)

target_link_libraries(
srdr_renderer
PUBLIC
    srdr_core
    srdr_platform
)
