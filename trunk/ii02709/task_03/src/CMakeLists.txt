cmake_minimum_required(VERSION 3.15)
project(PID_Lab3_ii02709 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pid_sim_ii02709 main.cpp pid_controller.cpp model.cpp)
target_include_directories(pid_sim_ii02709 PRIVATE .)