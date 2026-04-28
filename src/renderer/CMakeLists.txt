set(
SRDR_RENDERER_HEADERS
    Renderer.hpp

    stage/VertexLoader.hpp
    stage/VertexShader.hpp
    stage/PrimitiveAssembler.hpp
    stage/Rasterizer.hpp
    stage/FragmentShader.hpp
    stage/OutputMerger.hpp

    shader_interfaces/FrameBuffer.hpp
    shader_interfaces/ColorAttachment.hpp
    shader_interfaces/DepthAttachment.hpp
    shader_interfaces/Vertex.hpp
    shader_interfaces/Primitive.hpp
    shader_interfaces/Fragment.hpp

    scene/Camera.hpp
)

set(
SRDR_RENDERER_SOURCES
    Renderer.cpp

    stage/VertexLoader.cpp
    stage/VertexShader.cpp
    stage/PrimitiveAssembler.cpp
    stage/Rasterizer.cpp
    stage/FragmentShader.cpp
    stage/OutputMerger.cpp

    shader_interfaces/FrameBuffer.cpp
    shader_interfaces/ColorAttachment.cpp
    shader_interfaces/DepthAttachment.cpp

    scene/Camera.cpp
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
