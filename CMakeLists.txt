cmake_minimum_required(VERSION 3.0)

project(Machina LANGUAGES C CXX)

file(GLOB_RECURSE src_folder src/*.cpp)
file(GLOB_RECURSE inc_folder include/*.hpp)

add_executable(machina ${src_folder} ${inc_folder})

target_include_directories(machina PRIVATE "include")

target_compile_options(machina PRIVATE -Wall -Wextra -Werror -ansi -pedantic)
target_compile_features(machina PRIVATE cxx_std_20)
