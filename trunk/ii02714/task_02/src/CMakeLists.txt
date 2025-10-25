cmake_minimum_required (VERSION 3.5)
project(task_02_ii02714_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    otis2.cpp
    
    Solution.h
    Solution.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})