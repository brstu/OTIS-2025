cmake_minimum_required(VERSION 3.5)
project(ii02711_test3)

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
  ii02711_test3
  test.cpp
  ../src/Model.cpp
)

target_link_libraries(
  ii02711_test3
  PRIVATE
  gtest
  gtest_main
  gmock
)

target_compile_options(ii02711_test3 PRIVATE --coverage -g -O0)
target_link_options(ii02711_test3 PRIVATE --coverage)

include(GoogleTest)
gtest_discover_tests(ii02711_test3)