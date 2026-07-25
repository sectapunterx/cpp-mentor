cmake_minimum_required(VERSION 3.24)
project({{PROJECT}} CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release)
endif()

option({{NS_UPPER}}_BUILD_TESTS "Build unit tests" ON)
option({{NS_UPPER}}_BUILD_APPS "Build command-line front-ends" ON)

# Header-only public API lives under include/{{NS}}/**. Consumers link {{NS}}::{{PROJECT}}.
add_library({{NS}}_{{PROJECT}} INTERFACE)
add_library({{NS}}::{{PROJECT}} ALIAS {{NS}}_{{PROJECT}})
target_include_directories({{NS}}_{{PROJECT}} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_features({{NS}}_{{PROJECT}} INTERFACE cxx_std_20)

if({{NS_UPPER}}_BUILD_APPS)
  add_subdirectory(src)
endif()

if({{NS_UPPER}}_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
