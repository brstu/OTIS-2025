# Конфигурация проекта для системы моделирования
cmake_minimum_required(VERSION 3.25)

# Настройка проекта
project(SystemSimulatorProject)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Загрузка фреймворка для тестирования
include(FetchContent)
FetchContent_Declare(
    testing_framework
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "Использовать общую CRT" FORCE)
FetchContent_MakeAvailable(testing_framework)

# Включение системы тестирования
enable_testing()

# Создание исполняемого файла для тестов
add_executable(
    system_simulator_tests
    ${CMAKE_CURRENT_SOURCE_DIR}/functions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../test/test.cpp
)

# Настройка директорий с заголовочными файлами
target_include_directories(system_simulator_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../test
)

# Подключение библиотек тестирования
target_link_libraries(
    system_simulator_tests
    GTest::gtest_main
)

# Автоматическая регистрация тестов
include(GoogleTest)
gtest_discover_tests(system_simulator_tests)