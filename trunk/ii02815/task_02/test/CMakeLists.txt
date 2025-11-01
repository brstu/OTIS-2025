cmake_minimum_required(VERSION 3.5)
project(model_tests)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")

include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(../src)
add_library(model STATIC ../src/model.cpp)

add_executable(main_exec ../src/main.cpp)
target_link_libraries(main_exec model)

add_executable(model_tests test.cpp)
target_link_libraries(model_tests model gtest_main)

include(GoogleTest)
gtest_discover_tests(model_tests)
