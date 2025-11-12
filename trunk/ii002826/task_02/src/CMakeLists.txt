cmake_minimum_required(VERSION 4.1.2)
project(task_02_ii002826)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Тестовое приложение
add_executable(model_tests ../test/test_models.cpp)
target_link_libraries(model_tests GTest::gtest GTest::gtest_main)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_test(NAME ModelTests COMMAND model_tests)