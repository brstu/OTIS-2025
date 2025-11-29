cmake_minimum_required(VERSION 3.16)

project(ii02709_pid_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ii02709_pid STATIC
    pid.cpp
    plant.cpp
)

target_include_directories(ii02709_pid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ii02709_simulator main.cpp)
target_link_libraries(ii02709_simulator PRIVATE ii02709_pid)

if(ENABLE_COVERAGE_II02709)
    target_compile_options(ii02709_pid PRIVATE --coverage)
    target_link_options(ii02709_pid PRIVATE --coverage)
    target_compile_options(ii02709_simulator PRIVATE --coverage)
    target_link_options(ii02709_simulator PRIVATE --coverage)
endif()
