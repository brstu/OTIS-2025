cmake_minimum_required (VERSION 3.5)
project(task_03_ii02710_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/pid_controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pid_controller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/simulation.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})