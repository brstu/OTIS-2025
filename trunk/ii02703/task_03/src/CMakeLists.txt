cmake_minimum_required(VERSION 3.5)

project(temperature_controller
    LANGUAGES CXX
    VERSION 1.0
)

add_library(PID_lib
    ./PID.cpp
    ./PID.h
)

add_executable(pid_simulator
    ./otis3.cpp
)

target_link_libraries(pid_simulator PRIVATE PID_lib)