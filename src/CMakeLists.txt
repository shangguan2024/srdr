cmake_minimum_required(VERSION 3.7...3.31)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
srdr
VERSION 0.1
DESCRIPTION "A Software Renderer"
LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set a cmake variable to true and define a corresponding C/C++ definition
function(set_flag flagValue)
    set(${flagValue} TRUE PARENT_SCOPE)
    add_definitions(-D${flagValue})
endfunction()

if(WIN32)
    set_flag(SRDR_SYSTEM_WINDOWS)
endif()

# Core support code, not specific to this project
set(
SRDR_CORE_INCLUDES
    ${PROJECT_SOURCE_DIR}/core
)
add_subdirectory(core)

# Platform
set(
SRDR_PLATFORM_INCLUDES
    ${PROJECT_SOURCE_DIR}/platform
)
add_subdirectory(platform)

# Renderer
set(
SRDR_RENDERER_INCLUDES
    ${PROJECT_SOURCE_DIR}/renderer
    ${PROJECT_SOURCE_DIR}/renderer/shader_interfaces
)
add_subdirectory(renderer)

# Application
set(
SRDR_APPLICATION_INCLUDES
    ${PROJECT_SOURCE_DIR}/application
    ${PROJECT_SOURCE_DIR}/application/examples
)
add_subdirectory(application)
