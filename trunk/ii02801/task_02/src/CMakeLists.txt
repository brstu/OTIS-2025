cmake_minimum_required(VERSION 3.25)
project(ii02801_task02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Загрузка GoogleTest ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- Добавляем исполняемый файл для тестов ---
add_executable(
  runTests_ii02801
  ${CMAKE_CURRENT_SOURCE_DIR}/functions.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../test/test.cpp
)

# --- Пути к заголовочным файлам ---
target_include_directories(runTests_ii02801 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../test
)

# --- Линковка с GoogleTest ---
target_link_libraries(
  runTests_ii02801
  GTest::gtest_main
)

# --- Автоматическое обнаружение тестов ---
include(GoogleTest)
gtest_discover_tests(runTests_ii02801)
