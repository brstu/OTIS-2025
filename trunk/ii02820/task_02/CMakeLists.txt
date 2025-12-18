cmake_minimum_required(VERSION 3.14)  # Увеличиваем версию для совместимости
project(task_02_ii02820)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги покрытия кода (gcov)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Основная программа
add_executable(task_02_main src/main.cpp src/model.cpp)
target_compile_options(task_02_main PRIVATE --coverage -g -O0)
target_link_options(task_02_main PRIVATE --coverage)

# Загрузка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Тесты
enable_testing()

add_executable(
  task_02_tests
  test/test_model.cpp
  src/model.cpp
)

target_include_directories(task_02_tests PRIVATE src)

target_link_libraries(
  task_02_tests
  PRIVATE
  gtest
  gtest_main
)

target_compile_options(task_02_tests PRIVATE --coverage -g -O0)
target_link_options(task_02_tests PRIVATE --coverage)

include(GoogleTest)
gtest_discover_tests(task_02_tests)