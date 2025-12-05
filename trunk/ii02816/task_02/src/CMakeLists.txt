cmake_minimum_required (VERSION 3.5)
project (task_02_ii02816_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (${PROJECT_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/functions.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/functions.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)