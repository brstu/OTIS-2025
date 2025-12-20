cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  my_tests
  ${CMAKE_CURRENT_SOURCE_DIR}/task_01.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../test/test.cpp
)

target_include_directories(my_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${CMAKE_CURRENT_SOURCE_DIR}/../test
)

target_link_libraries(
  my_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(my_tests)