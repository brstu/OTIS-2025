cmake_minimum_required(VERSION 3.20)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

add_executable(unit_tests test_model.cpp)

target_link_libraries(unit_tests PRIVATE gtest gtest_main mylib)

add_test(NAME AllTests COMMAND unit_tests)
