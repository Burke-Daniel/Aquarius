cmake_minimum_required(VERSION 3.10)

project(Aquarius-Engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(sources test.cpp)

add_executable(Aquarius-Engine ${sources})

target_link_libraries(Aquarius-Engine glad)
target_link_libraries(Aquarius-Engine glfw ${GLFW_LIBRARIES})
target_link_libraries(Aquarius-Engine glm::glm)
target_link_libraries(Aquarius-Engine easyloggingpp)
target_link_libraries(Aquarius-Engine stb_image)
