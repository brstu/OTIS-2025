cmake_minimum_required (VERSION 3.5)
project(OTIS_task_02_ii02812_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES main.cpp functions.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})