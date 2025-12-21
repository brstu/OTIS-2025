cmake_minimum_required(VERSION 3.10.0)

# Используйте правильное имя для вашей группы (ii02710)
add_executable(runTests_ii02710 test.cpp ../src/model.cpp)

# Добавляем путь к заголовочным файлам
target_include_directories(runTests_ii02710 PRIVATE ../src)

# Линкуем с Google Test
target_link_libraries(runTests_ii02710 gtest gtest_main)

# Добавляем тест
add_test(NAME task_02_tests COMMAND runTests_ii02710)