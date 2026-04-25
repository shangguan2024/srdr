set(
SRDR_APPLICATION_HEADERS
    examples/ExampleWindowTest.hpp
)

set(
SRDR_APPLICATION_SOURCES
    app.cpp

    examples/ExampleWindowTest.cpp
)

add_executable(srdr ${SRDR_APPLICATION_HEADERS} ${SRDR_APPLICATION_SOURCES})

target_include_directories(
srdr
PUBLIC
    ${SRDR_APPLICATION_INCLUDES}
    ${SRDR_CORE_INCLUDES}
    ${SRDR_PLATFORM_INCLUDES}
    ${SRDR_RENDERER_INCLUDES}
)

target_link_libraries(
srdr
PRIVATE
    srdr_core
    srdr_platform
    srdr_renderer
)
