cmake_minimum_required(VERSION 3.0)


# Find all headers directories to include in project path
MACRO(SCAN_INCLUDES return_list)
    FILE(GLOB_RECURSE new_list *.hpp)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()


# Project setup
project(Machina LANGUAGES C CXX)

SCAN_INCLUDES(inc_files)
list(LENGTH inc_files inc_files_count)
message(STATUS "[INFO] Found ${inc_files_count} header directories.")

include_directories(PUBLIC ${inc_files})

file(GLOB_RECURSE src_folder src/*.cpp)
file(GLOB_RECURSE inc_folder include/*.hpp)

add_executable(machina ${src_folder} ${inc_folder})

target_compile_options(machina PRIVATE -Wall -Wextra -Werror -ansi -pedantic)
target_compile_features(machina PRIVATE cxx_std_20)
