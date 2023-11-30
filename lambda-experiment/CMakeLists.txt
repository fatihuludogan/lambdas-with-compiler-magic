cmake_minimum_required(VERSION 3.21)
project(lambda-experiment)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(oneValueArgs TARGET ENABLE AS_ERRORS)
cmake_parse_arguments(
    TARGET_SET_WARNINGS
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN})

if(NOT ${TARGET_SET_WARNINGS_ENABLE})
    message(STATUS "Warnings Disabled for: ${TARGET_SET_WARNINGS_TARGET}")
    return()
endif()
message(STATUS "Warnings Active for: ${TARGET_SET_WARNINGS_TARGET}")
message(STATUS "Warnings as Errors: ${TARGET_SET_WARNINGS_AS_ERRORS}")

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
