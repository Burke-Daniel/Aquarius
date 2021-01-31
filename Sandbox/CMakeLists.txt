cmake_minimum_required(VERSION 3.10)

project(Sandbox)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(sources Sandbox.cpp)

add_executable(Sandbox ${sources})

target_link_libraries(Sandbox Aquarius-Engine)
