set(
SRDR_PLATFORM_HEADERS
    IWindow.hpp
    WindowFactory.hpp
)

set(
SRDR_PLATFORM_SOURCES
    WindowFactory.cpp
)

if(WIN32)
    list(APPEND SRDR_PLATFORM_HEADERS Win32Window.hpp)
    list(APPEND SRDR_PLATFORM_SOURCES Win32Window.cpp)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

add_library(
srdr_platform
STATIC
    ${SRDR_PLATFORM_HEADERS}
    ${SRDR_PLATFORM_SOURCES}
)

target_include_directories(
srdr_platform
PUBLIC
    ${SRDR_PLATFORM_INCLUDES}
    ${SRDR_CORE_INCLUDES}
)

target_link_libraries(
srdr_platform
PUBLIC
    srdr_core
)
