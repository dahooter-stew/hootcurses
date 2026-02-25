cmake_minimum_required(VERSION 3.19)

add_library(linked_list STATIC src/linked_list.c)
target_include_directories(linked_list PUBLIC include)
