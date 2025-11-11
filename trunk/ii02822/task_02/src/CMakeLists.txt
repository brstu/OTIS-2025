cmake_minimum_required(VERSION 3.14)
project(TemperatureModel)

set(CMAKE_CXX_STANDARD 14)

add_executable(
    temperature_model
    main.cpp
    functions.cpp
)