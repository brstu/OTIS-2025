cmake_minimum_required(VERSION 3.14)
project(task_02_ii002817 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==================== ОСНОВНОЕ ПРИЛОЖЕНИЕ ====================
add_executable(${PROJECT_NAME} main.cpp laba2otis.cpp)

# ==================== GOOGLE TEST ====================
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ==================== ТЕСТОВОЕ ПРИЛОЖЕНИЕ ====================
add_executable(
  model_tests
  laba2otis.cpp  # исходный код из текущей папки src
  ../test/test_lab2.cpp  # тесты из папки test
)

# Подключаем заголовочные файлы
target_include_directories(model_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}  # для lab2otis.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../test  # для тестов если нужно
)

# Линковка библиотек
target_link_libraries(
  model_tests
  GTest::gtest_main
)

# Автоматическое обнаружение тестов
include(GoogleTest)
gtest_discover_tests(model_tests)