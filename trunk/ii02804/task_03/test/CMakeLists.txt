cmake_minimum_required(VERSION 3.20)
project(unit_tests)

set(CMAKE_CXX_STANDARD 23)

# Подключаем GoogleTest
add_subdirectory("../third_party/googletest-main" "${CMAKE_BINARY_DIR}/googletest_build")

# Подключаем заголовки src
include_directories("../src")

# Тестируемая библиотека core
add_library(core STATIC 
    "../src/main.cpp"
    "../src/pid.cpp"
    "../src/models.cpp"
)

# Исполняемый файл для тестов
add_executable(unit_tests test_pid.cpp)

# Линкуем с core и gtest
target_link_libraries(unit_tests PRIVATE core gtest gtest_main)

enable_testing()
add_test(NAME unit_tests COMMAND unit_tests)
