cmake_minimum_required(VERSION 3.15.0)
project(main VERSION 0.1.0 LANGUAGES C CXX)

add_executable(main main.cpp)

include(CTest)
enable_testing()

