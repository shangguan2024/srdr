set(
SRDR_CORE_HEADERS
    Vector.hpp
    Color.hpp
)

set(
SRDR_CORE_SOURCES
    Color.cpp
)

add_library(
srdr_core
STATIC
    ${SRDR_CORE_HEADERS}
    ${SRDR_CORE_SOURCES}
)

target_include_directories(
srdr_core
PUBLIC
    ${SRDR_CORE_INCLUDES}
)
