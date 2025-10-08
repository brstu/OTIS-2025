cmake_minimum_required(VERSION 3.5)

project(task_01_ii02709 LANGUAGES CXX)

message(STATUS "CMake configuration started by kozel")

add_executable(otis_2025 lab1.cpp)

set_target_properties(otis_2025 PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

option(KOZEL_SPECIAL_FEATURE "Включить особую фичу Kozel" OFF)

if(KOZEL_SPECIAL_FEATURE)
    target_compile_definitions(otis_2025 PRIVATE KOZEL_FEATURE_ENABLED)
    message(STATUS "Активирована специальная опция kozel")
endif()
