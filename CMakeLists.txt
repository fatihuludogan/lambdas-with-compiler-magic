cmake_minimum_required(VERSION 3.21)
project("lambdas-with-compiler-magic")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_23)

include(${CMAKE_TOOLCHAIN_FILE})    # vcpkg.cmake
find_package(fmt REQUIRED)

option(ENABLE_BUILD_WITH_TIME_TRACE
    "Enable -ftime-trace to generate time tracing .json files on clang" ON)
if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
endif()

add_compile_options(
  -O1 -g -flto -S
  -fsanitize=address -fsanitize=memory
  -fno-omit-frame-pointer
)

add_link_options(
    -g -flto -S 
    -fsanitize=address
)

target_link_libraries(PRIVATE fmt::fmt)

add_subdirectory("lambda-experiment")