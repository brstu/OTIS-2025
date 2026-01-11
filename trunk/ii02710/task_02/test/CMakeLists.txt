cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Используйте правильное имя для вашей группы (ii02710)
add_executable(runTests_ii02710 test.cpp ../src/model.cpp)

# Добавляем путь к заголовочным файлам
target_include_directories(runTests_ii02710 PRIVATE ../src)

# Линкуем с Google Test
target_link_libraries(runTests_ii02710 gtest gtest_main)

# Добавляем тест
add_test(NAME task_02_tests COMMAND runTests_ii02710)
target_compile_options(runTests_ii02710 PRIVATE --coverage -g -O0)
target_link_options(runTests_ii02710 PRIVATE --coverage)