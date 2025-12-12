cmake_minimum_required(VERSION 3.5)
project(PID_Controller_ii02815)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})

include(FetchContent)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(ii02815_pid_simulation
main3.cpp
pid_contr.cpp
model.cpp
)

add_executable(ii02815_pid_tests
../test/test_pid.cpp
pid_contr.cpp
model.cpp
)

target_link_libraries(ii02815_pid_tests gtest_main)

target_include_directories(ii02815_pid_simulation PRIVATE .)
target_include_directories(ii02815_pid_tests PRIVATE .)