cmake_minimum_required(VERSION 3.15.0)
project(wape VERSION 0.1.0 LANGUAGES C CXX)

add_executable(wape main.cpp model.cpp)

include(CTest)
enable_testing()

