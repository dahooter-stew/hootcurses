cmake_minimum_required(VERSION 3.19)

project(hootcurses C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(libs/resizable_array)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})
#add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES} bt.rc) #with icon

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE resizable_array)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
