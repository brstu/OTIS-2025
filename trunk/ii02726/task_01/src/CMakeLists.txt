cmake_minimum_required(VERSION 3.16)

project(YushkevichProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_compile_options(-Wall -Wextra -Wpedantic)

set(SOURCE_FILES
    otis_task_01.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)