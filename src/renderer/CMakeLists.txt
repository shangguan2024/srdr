add_library(
    srdr_renderer
    STATIC
    FrameBuffer.cpp
)

target_include_directories(
    srdr_renderer
    PUBLIC
    ${SRDR_CORE_INCLUDES}
    ${SRDR_PLATFORM_INCLUDES}
)

target_link_libraries(
    srdr_renderer
    PUBLIC
    srdr_platform
)
