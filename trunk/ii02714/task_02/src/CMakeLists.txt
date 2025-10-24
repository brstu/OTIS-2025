cmake_minimum_required(VERSION 3.14)  # 🔧 Обновлено для устранения предупреждения

project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная библиотека с классом Obj
add_library(solution STATIC Solution.cpp)
target_include_directories(solution PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Основной исполняемый файл
add_executable(task_02 otis2.cpp)
target_link_libraries(task_02 PRIVATE solution)

# Настройка Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тесты
add_executable(runTests test/test.cpp)  # 🔧 Уточнён путь к тесту
target_link_libraries(runTests PRIVATE solution gtest gtest_main)

# Регистрация тестов
include(GoogleTest)
gtest_discover_tests(runTests)
