cmake_minimum_required(VERSION 3.10)

project(glad)

include_directories(include)
set(sources src/glad.c)

add_library(glad STATIC ${sources})
