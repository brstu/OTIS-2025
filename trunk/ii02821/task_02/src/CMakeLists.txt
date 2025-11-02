cmake_minimum_required(VERSION 3.10)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(main
    main.cpp
    model.cpp
)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тесты
add_executable(runTests
    ../test/testmodel.cpp
    model.cpp
)
target_link_libraries(runTests GTest::gtest GTest::gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(runTests)