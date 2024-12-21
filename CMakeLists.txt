cmake_minimum_required(VERSION 3.13)

project(iter74 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "-Wno-gnu-alignof-expression ${CMAKE_C_FLAGS}")

set(MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
list(REMOVE_ITEM SRC_FILES ${MAIN_SRC})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${MAIN_SRC})

target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined,leak -g -O1)
target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined,leak)

enable_testing()

add_subdirectory(tests)
