cmake_minimum_required(VERSION 3.16)
project(otis3_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  otis3_test
  test.cpp
  ../src/PID.cpp
)

target_link_libraries(
  otis3_test
  PRIVATE
  gtest
  gtest_main
  gmock
)

target_compile_options(otis3_test PRIVATE --coverage -g -O0)
target_link_options(otis3_test PRIVATE --coverage)

include(GoogleTest)
gtest_discover_tests(otis3_test)
