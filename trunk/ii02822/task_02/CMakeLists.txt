cmake_minimum_required(VERSION 3.25)
project(ii02822_task02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Главная программа
add_executable(main_program 
    main.cpp
    functions.cpp
)

# Тесты
add_executable(runTests_ii02822
    ../test/test_functions.cpp
    functions.cpp
)

target_include_directories(runTests_ii02822 PRIVATE
    .
    test
)

target_link_libraries(
  runTests_ii02822
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTests_ii02822)