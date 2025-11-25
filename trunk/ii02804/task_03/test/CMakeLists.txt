cmake_minimum_required(VERSION 3.15)
project(task_03_ii02804_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем флаги для покрытия кода
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# Подключаем GoogleTest через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Пути к исходникам для тестов
include_directories("../src")

# Собираем исполняемый тестовый бинарник
add_executable(unit_tests
    test_pid.cpp
    ../src/pid.cpp
    ../src/models.cpp
)

# Линкуем GoogleTest
target_link_libraries(unit_tests PRIVATE gtest gtest_main gmock)

# Флаги для покрытия
target_compile_options(unit_tests PRIVATE --coverage -g -O0)
target_link_options(unit_tests PRIVATE --coverage)

# Автоматический запуск тестов через CTest
include(GoogleTest)
gtest_discover_tests(unit_tests)
