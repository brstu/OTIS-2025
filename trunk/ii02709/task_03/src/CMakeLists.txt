cmake_minimum_required(VERSION 3.16)

project(ii02709_task03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_COVERAGE_II02709 "Enable coverage flags" OFF)

if(ENABLE_COVERAGE_II02709)
    add_compile_options(--coverage -O0)
    add_link_options(--coverage)
endif()

add_library(ii02709_core
    pid.cpp
    plant.cpp
)

target_include_directories(ii02709_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ii02709_simulator
    main.cpp
)

target_include_directories(ii02709_simulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ii02709_simulator PRIVATE ii02709_core)
