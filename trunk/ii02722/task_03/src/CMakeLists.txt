cmake_minimum_required(VERSION 3.14)
project(ii002722_task_03 LANGUAGES CXX)

# General settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Strict warnings
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Fix paths - use relative paths
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../test)
set(DOC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../doc)

# Project libraries
add_library(model_ii002722 STATIC ${SRC_DIR}/model.cpp)
target_include_directories(model_ii002722 PUBLIC ${SRC_DIR})

# Fix: Имя библиотеки должно быть согласовано
add_library(pid_ii002722 STATIC ${SRC_DIR}/pid.cpp)
target_include_directories(pid_ii002722 PUBLIC ${SRC_DIR})

# Main executable
add_executable(pid_sim ${SRC_DIR}/main.cpp)
target_link_libraries(pid_sim PRIVATE pid_ii002722 model_ii002722)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# Tests
if(EXISTS ${TEST_DIR})
    add_executable(runTests ${TEST_DIR}/test_pid.cpp)
    target_link_libraries(runTests PRIVATE gtest_main pid_ii002722 model_ii002722)
    target_include_directories(runTests PRIVATE ${SRC_DIR})
    gtest_discover_tests(runTests)
else()
    message(WARNING "Test directory not found: ${TEST_DIR}")
endif()