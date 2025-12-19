cmake_minimum_required(VERSION 3.5)
project(task_03_ii02702_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  ${PROJECT_NAME}
  test.cpp
  ../src/models.hpp
  ../src/models.cpp
  ../src/pid.hpp
  ../src/pid.cpp
)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  gtest
  gtest_main
  gmock
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})