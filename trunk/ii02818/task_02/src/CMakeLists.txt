cmake_minimum_required(VERSION 3.14)
project(task_02_ii02818 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# СОЗДАЕМ ТОЛЬКО ОДИН ИСПОЛНЯЕМЫЙ ФАЙЛ С УНИКАЛЬНЫМ ИМЕНЕМ
add_executable(
  ${PROJECT_NAME}_model_tests  # УНИКАЛЬНОЕ ИМЯ
  laba2otis.cpp
  ../test/test_lab2.cpp
)

target_include_directories(${PROJECT_NAME}_model_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../test
)

target_link_libraries(
  ${PROJECT_NAME}_model_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_model_tests)