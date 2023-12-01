cmake_minimum_required(VERSION 3.21)
project(lambda-experiment)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#[[
add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-Wshadow)
add_definitions(-Wpedantic)
add_definitions(-Wunused)
add_definitions(-Wformat=2)
add_definitions(-Wcast-align)
add_definitions(-Wconversion)
add_definitions(-Wsign-conversion)
add_definitions(-Wnull-dereference)
add_definitions(-Wdouble-promotion)
add_definitions(-Wnon-virtual-dtor)
add_definitions(-Wold-style-cast)
add_definitions(-Woverloaded-virtual)
add_definitions(-Weffc++)
add_definitions(-Wno-unused-private-field)
add_definitions(-Wno-unneeded-internal-declaration)
]]

# add_library(lambda-lib "${CMAKE_CURRENT_SOURCE_DIR}/src/lambda-w-compiler-magic/magic-w-lambdas.hpp")

add_executable(lambda-src "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
                          "${CMAKE_CURRENT_SOURCE_DIR}/src/lambda-w-compiler-magic/magic-w-lambdas.cpp")