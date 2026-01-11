cmake_minimum_required(VERSION 3.14)
project(ii02821_ruslan_task_03 LANGUAGES CXX)

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

# Paths
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../test)
set(DOC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../doc)

# Project libraries
add_library(model_ruslan STATIC ${SRC_DIR}/model_ruslan.cpp)
target_include_directories(model_ruslan PUBLIC ${SRC_DIR})

add_library(pid_ruslan STATIC ${SRC_DIR}/pid_ruslan.cpp)
target_include_directories(pid_ruslan PUBLIC ${SRC_DIR})

# Main executable
add_executable(pid_sim_ruslan ${SRC_DIR}/main_ruslan.cpp)
target_link_libraries(pid_sim_ruslan PRIVATE pid_ruslan)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# Tests
file(GLOB TEST_SOURCES "${TEST_DIR}/test_pid_ruslan.cpp")
if(TEST_SOURCES)
    add_executable(runTests_ruslan_task03 ${TEST_SOURCES})
    target_link_libraries(runTests_ruslan_task03 PRIVATE gtest_main pid_ruslan model_ruslan)
    gtest_discover_tests(runTests_ruslan_task03)
else()
    message(WARNING "Test files not found in ${TEST_DIR}")
endif()