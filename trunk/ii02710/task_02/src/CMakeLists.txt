cmake_minimum_required (VERSION 3.10.0)
project(task_02_ii02710_src)

set(PROJECT_SOURCES
    task_02.cpp
    model.cpp
    model.h
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
