cmake_minimum_required (VERSION 3.5)
project (task_03_ii02702_src)

set(PROJECT_SOURCES
    main.cpp
    modelsAndPID.hpp
    modelsAndPID.cpp
    pid.hpp
    pid.cpp
)

add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})