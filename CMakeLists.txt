cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_REQUIRED_FLAGS -std=c++17)

project(Aquarius)

include_directories(${PROJECT_SOURCE_DIR}/Aquarius)
include_directories(${PROJECT_SOURCE_DIR}/Aquarius/Src)
include_directories(${PROJECT_SOURCE_DIR}/Aquarius/Vendor/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/Aquarius/Vendor/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/Aquarius/Vendor/easyloggingpp/src)
include_directories(${PROJECT_SOURCE_DIR}/Aquarius/Vendor/stb_image)

# So that easylogging++ is build as a static lib
set(build_static_lib ON CACHE BOOL "build static library" FORCE)

# Find GLM
set(glm_DIR Aquarius/Vendor/glm/cmake/glm)
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

# Add other subprojects
add_subdirectory(Aquarius)
add_subdirectory(Aquarius/Vendor/easyloggingpp)
add_subdirectory(Aquarius/Vendor/glad)
add_subdirectory(Aquarius/Vendor/glfw)
add_subdirectory(Aquarius/Vendor/stb_image)
add_subdirectory(Sandbox)
