cmake_minimum_required(VERSION 3.10)

project(Sandbox)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions(-DGLFW_INCLUDE_NONE)

file(GLOB TOP_LEVEL_FILES *.h *.cpp)
file(GLOB_RECURSE RPG_SOURCES "RPG/*.cpp" "RPG/*.h")
file(GLOB_RECURSE PONG_SOURCES "Pong/*.cpp" "Pong/*.h")

source_group("" FILES ${TOP_LEVEL_FILES})
source_group("RPG" FILES ${RPG_SOURCES})
source_group("Pong" FILES ${PONG_SOURCES})

add_executable(Sandbox ${TOP_LEVEL_FILES}
					   ${RPG_SOURCES}
					   ${PONG_SOURCES})

target_link_libraries(Sandbox Aquarius-Engine)
