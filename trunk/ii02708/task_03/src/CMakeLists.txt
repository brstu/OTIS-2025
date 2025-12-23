cmake_minimum_required (VERSION 3.5)
project (task_03_ii02708_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SRC
    main.cpp
    nonlinear.h
    pid.h
)

add_executable ( ${PROJECT_NAME} ${PROJECT_SRC} )