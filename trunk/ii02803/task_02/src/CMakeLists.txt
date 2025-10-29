cmake_minimum_required(VERSION 3.20)
project(ii02803_Task02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходникам
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Основные файлы программы (если нужно собирать основной exe)
add_executable(ii02803_Task02
    ${CMAKE_CURRENT_SOURCE_DIR}/functions.cpp
)

# ---- Подключение GoogleTest через vcpkg ----
find_package(GTest CONFIG REQUIRED)

# ---- Тесты ----
add_executable(runTests_ii02803
    ${CMAKE_CURRENT_SOURCE_DIR}/functions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../test/test.cpp
)

# Линкуем GoogleTest
target_link_libraries(runTests_ii02803 PRIVATE GTest::gtest GTest::gtest_main)

# Включаем автоматический запуск тестов через ctest
enable_testing()
include(GoogleTest)
gtest_discover_tests(runTests_ii02803)
