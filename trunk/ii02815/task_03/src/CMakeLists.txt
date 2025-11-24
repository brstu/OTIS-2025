cmake_minimum_required(VERSION 3.5)
project(PID_Controller_ii02815)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})

include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(pid_simulation
main3.cpp
pid_contr.cpp
model.cpp
)

add_executable(pid_tests
../test/test_pid.cpp
pid_contr.cpp
model.cpp
)

target_link_libraries(pid_tests gtest_main)

target_include_directories(pid_simulation PRIVATE .)
target_include_directories(pid_tests PRIVATE .)