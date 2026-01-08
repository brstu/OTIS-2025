cmake_minimum_required(VERSION 3.16)
project(ii02721)

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
  ii02721
  test.cpp
  ../src/n_linear.cpp
)

target_link_libraries(
  ii02721
  PRIVATE
  gtest
  gtest_main
  gmock
)

target_compile_options(ii02721 PRIVATE --coverage -g -O0)
target_link_options(ii02721 PRIVATE --coverage)

include(GoogleTest)
gtest_discover_tests(ii02721)