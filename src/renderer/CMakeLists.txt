set(
SRDR_RENDERER_HEADERS
    FrameBuffer.hpp
)

set(
SRDR_RENDERER_SOURCES
    FrameBuffer.cpp
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
