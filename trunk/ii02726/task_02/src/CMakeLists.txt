cmake_minimum_required(VERSION 3.14)

project(lab2_src LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(test STATIC
    test.cpp
)

target_include_directories(test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(otis_task_02_app
    otis_task_02.cpp
)

target_link_libraries(otis_task_02_app PRIVATE test)

if (MSVC)
    target_compile_options(test PRIVATE /W4)
    target_compile_options(test_app PRIVATE /W4)
else()
    target_compile_options(test PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(test_app PRIVATE -Wall -Wextra -pedantic)
endif()