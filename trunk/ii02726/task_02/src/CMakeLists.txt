cmake_minimum_required(VERSION 3.16...3.31)
project(task_02)

set(CMAKE_CXX_STANDARD 17)

add_executable(main otis_task_02.cpp test.cpp)

enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.14.0.zip
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(runTests ../test/test_test.cpp test.cpp)
target_link_libraries(runTests GTest::GTest GTest::Main pthread)
target_include_directories(runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME runTests COMMAND runTests)
