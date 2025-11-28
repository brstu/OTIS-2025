cmake_minimum_required(VERSION 3.15)
project(PID_Lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pid_sim_ii02709
    main.cpp
    pid_controller.cpp
    model.cpp
)

target_include_directories(pid_sim_ii02709 PRIVATE .)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(pid_sim_ii02709 PRIVATE -O0 -g --coverage)
    target_link_options(pid_sim_ii02709 PRIVATE --coverage)
endif()