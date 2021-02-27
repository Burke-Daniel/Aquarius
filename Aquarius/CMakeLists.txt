cmake_minimum_required(VERSION 3.10)

project(Aquarius-Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions(-DGLFW_INCLUDE_NONE)

file(GLOB_RECURSE Sources "Src/*.cpp" "Src/*.h")

include_directories(Src/)

add_library(Aquarius-Engine STATIC ${Sources} Aquarius.h)

target_link_libraries(Aquarius-Engine glad)
target_link_libraries(Aquarius-Engine glfw ${GLFW_LIBRARIES})
target_link_libraries(Aquarius-Engine glm::glm)
target_link_libraries(Aquarius-Engine easyloggingpp)
target_link_libraries(Aquarius-Engine stb_image)
