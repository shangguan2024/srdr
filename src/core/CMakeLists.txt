set(
SRDR_CORE_HEADERS
    Color.hpp
    Vector.hpp
    Matrix.hpp
    Transform.hpp
    Geometry.hpp
)

set(
SRDR_CORE_SOURCES
    Color.cpp
    Transform.cpp
    Geometry.cpp
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
