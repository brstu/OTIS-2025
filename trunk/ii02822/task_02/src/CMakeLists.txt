cmake_minimum_required(VERSION 3.25)
project(ii02822_task02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Загрузка GoogleTest ---
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- Добавляем исполняемый файл для тестов ---
add_executable(
  runTests_ii02822
  functions.cpp                  
  ../test/test_functions.cpp      

# --- Пути к заголовочным файлам ---
target_include_directories(runTests_ii02822 PRIVATE
    .                          
    ../test                        
)

# --- Линковка с GoogleTest ---
target_link_libraries(
  runTests_ii02822
  GTest::gtest_main
)

# --- Автоматическое обнаружение тестов ---
include(GoogleTest)
gtest_discover_tests(runTests_ii02822)