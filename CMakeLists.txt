cmake_minimum_required(VERSION 3.0)


# Find all headers directories to include in project path
MACRO(SCAN_INCLUDES return_list)
    message("Headers found : ")
    FILE(GLOB_RECURSE new_list src/*.hpp)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        message(${file_path})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()



# Project setup
project(Machina LANGUAGES C CXX)

SCAN_INCLUDES(inc_files)
include_directories(PUBLIC ${inc_files})

file(GLOB_RECURSE src_files src/*.cpp)

add_executable(machina ${src_files} ${inc_files})

target_compile_options(machina PRIVATE -Wall -Wextra -Werror -ansi -pedantic)
target_compile_features(machina PRIVATE cxx_std_20)
