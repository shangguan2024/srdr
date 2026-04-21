set(
SRDR_RENDERER_HEADERS
    VertexLoader.hpp
    VertexShader.hpp
    PrimitiveAssembler.hpp
    Rasterizer.hpp
    PixelShader.hpp
    OutputMerger.hpp
    FrameBuffer.hpp
    Renderer.hpp
)

set(
SRDR_RENDERER_SOURCES
    VertexLoader.cpp
    VertexShader.cpp
    PrimitiveAssembler.cpp
    Rasterizer.cpp
    PixelShader.cpp
    OutputMerger.cpp
    FrameBuffer.cpp
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
