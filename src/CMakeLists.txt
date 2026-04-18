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

add_subdirectory(application)
add_subdirectory(renderer)
add_subdirectory(platform)
add_subdirectory(core)
