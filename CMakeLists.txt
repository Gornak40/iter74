cmake_minimum_required(VERSION 3.13)

project(iter74 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})


target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined -g -O1)
target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)

target_include_directories(${PROJECT_NAME} PRIVATE include)
