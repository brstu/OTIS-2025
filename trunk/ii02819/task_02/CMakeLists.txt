cmake_minimum_required(VERSION 3.14)
project(Task02)

set(CMAKE_CXX_STANDARD 17)

# Библиотека с функциями
add_library(src_lib src/models.cpp)

add_executable(main_app src/main.cpp)
target_link_libraries(main_app src_lib)

# Google Test через FetchContent
include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # исправление для MSVC
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(runTests test/test_models.cpp)
target_link_libraries(runTests src_lib gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)


