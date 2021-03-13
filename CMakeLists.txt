cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_REQUIRED_FLAGS -std=c++17)

project(Aquarius)

# Fix to threads error on MacOS, this will assume built-in pthreads
IF(APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
ENDIF()

include_directories(${PROJECT_SOURCE_DIR}/Aquarius)
include_directories(${PROJECT_SOURCE_DIR}/Aquarius/Src)
include_directories(${PROJECT_SOURCE_DIR}/Aquarius/Vendor/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/Aquarius/Vendor/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/Aquarius/Vendor/easyloggingpp/src)
include_directories(${PROJECT_SOURCE_DIR}/Aquarius/Vendor/openal-soft/include)
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
add_subdirectory(Aquarius/Vendor/openal-soft)
add_subdirectory(Aquarius/Vendor/stb_image)
add_subdirectory(Sandbox)
