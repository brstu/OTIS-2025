cmake_minimum_required (VERSION 3.12)
project(task_03_ii02719_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    main.cpp
	functions.h
	functions.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})