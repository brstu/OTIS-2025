cmake_minimum_required (VERSION 3.15)
project (task_02_ii02816_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SRC
    main.cpp
    l.h
    nonl.h
)

add_executable ( ${PROJECT_NAME} ${PROJECT_SRC} )