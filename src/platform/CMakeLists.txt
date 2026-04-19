set(PLATFORM_SOURCES WindowFactory.cpp)

if(WIN32)
    list(APPEND PLATFORM_SOURCES Win32Window.cpp)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

add_library(
    srdr_platform
    STATIC
    ${PLATFORM_SOURCES}
)

target_include_directories(
    srdr_platform
    PUBLIC
    ${SRDR_CORE_INCLUDES}
)
