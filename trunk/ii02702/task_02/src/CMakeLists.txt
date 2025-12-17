cmake_minimum_required (VERSION 3.5)
project (task_02_ii02702_src)

set(PROJECT_SOURCES
    main.cpp
    models.hpp
    models.cpp
)

add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})