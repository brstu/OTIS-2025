cmake_minimum_required (VERSION 3.5)
project(task_02_ii02710_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    task_02.cpp
    model.cpp
    model.h
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
