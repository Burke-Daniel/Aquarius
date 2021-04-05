cmake_minimum_required(VERSION 3.10)

project(imgui)

file(GLOB OPENGL_IMPL "backends/imgui_impl_opengl3.*")
file(GLOB GLFW_IMPL "backends/imgui_impl_glfw.*")
file(GLOB sources *.cpp *.h)

add_library(imgui STATIC ${sources}
                         ${OPENGL_IMPL}
                         ${GLFW_IMPL})
