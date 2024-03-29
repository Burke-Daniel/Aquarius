cmake_minimum_required(VERSION 3.10)

project(Aquarius-Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Subdirectory definitions
add_definitions(-DGLFW_INCLUDE_NONE)
set(LIBTYPE "STATIC")

file(GLOB_RECURSE CORE_SOURCES "Src/Aquarius/Core/*.cpp" "Src/Aquarius/Core/*.h")
file(GLOB_RECURSE EVENT_SOURCES "Src/Aquarius/Events/*.cpp" "Src/Aquarius/Events/*.h")
file(GLOB_RECURSE RENDERER_SOURCES "Src/Aquarius/Renderer/*.cpp" "Src/Aquarius/Renderer/*.h")
file(GLOB_RECURSE IMGUI_SOURCES "Src/Aquarius/Imgui/*.cpp" "Src/Aquarius/Imgui/*.h")
file(GLOB_RECURSE SOUND_SOURCES "Src/Aquarius/Sound/*.cpp" "Src/Aquarius/Sound/*.h")
set(TOP_LEVEL_FILES "Aquarius.h")

source_group("" FILES ${TOP_LEVEL_FILES})
source_group("Core" FILES ${CORE_SOURCES})
source_group("Events" FILES ${EVENT_SOURCES})
source_group("Renderer" FILES  ${RENDERER_SOURCES})
source_group("Imgui" FILES  ${IMGUI_SOURCES})
source_group("Sound" FILES ${SOUND_SOURCES})

include_directories(Src/)

add_library(Aquarius-Engine STATIC  ${TOP_LEVEL_FILES} 
									${CORE_SOURCES} 
									${EVENT_SOURCES} 
									${RENDERER_SOURCES}
									${IMGUI_SOURCES}
									${SOUND_SOURCES})

target_link_libraries(Aquarius-Engine glad)
target_link_libraries(Aquarius-Engine glfw ${GLFW_LIBRARIES})
target_link_libraries(Aquarius-Engine glm::glm)
target_link_libraries(Aquarius-Engine easyloggingpp)
target_link_libraries(Aquarius-Engine OpenAL)
target_link_libraries(Aquarius-Engine stb_image)
target_link_libraries(Aquarius-Engine AudioFile)
target_link_libraries(Aquarius-Engine imgui)
