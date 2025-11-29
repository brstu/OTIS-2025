cmake_minimum_required(VERSION 3.16)
project(ii02709_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()


add_subdirectory(../src ${CMAKE_CURRENT_BINARY_DIR}/src)


add_executable(ii02709_tests
    test_pid.cpp
)

target_include_directories(ii02709_tests PRIVATE
    ../src
)

target_link_libraries(ii02709_tests
    PRIVATE
        ii02709_core
        gtest_main
)


option(ENABLE_COVERAGE_II02709 "Enable coverage flags" ON)
if(ENABLE_COVERAGE_II02709)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(ii02709_tests PRIVATE --coverage -O0 -g)
        target_link_options(ii02709_tests PRIVATE --coverage)
        target_compile_options(ii02709_core PRIVATE --coverage -O0 -g)
        target_link_options(ii02709_core PRIVATE --coverage)
    endif()
endif()

include(GoogleTest)
gtest_discover_tests(ii02709_tests)