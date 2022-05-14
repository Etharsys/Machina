cmake_minimum_required(VERSION 3.0)

project(Machina LANGUAGES C CXX)

include_directories(${CMAKE_SOURCE_DIR}\\include)
include_directories(${CMAKE_SOURCE_DIR}\\include\\util)
include_directories(${CMAKE_SOURCE_DIR}\\include\\input)
include_directories(${CMAKE_SOURCE_DIR}\\include\\config)

file(GLOB_RECURSE src_folder src/*.cpp)
file(GLOB_RECURSE inc_folder include/*.hpp)

add_executable(machina ${src_folder} ${inc_folder})

target_compile_options(machina PRIVATE -Wall -Wextra -Werror -ansi -pedantic)
target_compile_features(machina PRIVATE cxx_std_20)
