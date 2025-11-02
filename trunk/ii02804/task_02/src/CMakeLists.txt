cmake_minimum_required(VERSION 3.14)
project(task_01)

# Используем C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Настройки для покрытия кода ---
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# --- GoogleTest ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- Создаем тестовый исполняемый файл ---
add_executable(
  my_tests
  ${CMAKE_CURRENT_SOURCE_DIR}/task_01.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../test/test.cpp
)

# Пути для include
target_include_directories(my_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}       # для task_01.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../test
)

# Линкуем GoogleTest
target_link_libraries(
  my_tests
  GTest::gtest_main
)

# Автоматический запуск тестов через CTest
include(GoogleTest)
gtest_discover_tests(my_tests)
