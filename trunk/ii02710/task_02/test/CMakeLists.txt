cmake_minimum_required(VERSION 3.14)

# Находим GoogleTest
find_package(GTest REQUIRED)

# Создаем тестовый исполняемый файл
add_executable(runTests_ii002713 test.cpp ../src/model.cpp)

# Линкуем с GoogleTest
target_link_libraries(runTests_ii002713 GTest::gtest GTest::gtest_main)

# Добавляем тест в CTest
add_test(NAME task_02_tests COMMAND runTests_ii002713)