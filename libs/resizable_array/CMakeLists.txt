cmake_minimum_required(VERSION 3.19)

add_library(resizable_array STATIC src/resizable_array.c)
target_include_directories(resizable_array PUBLIC include)
