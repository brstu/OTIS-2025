cmake_minimum_required(VERSION 3.16)

project(ii02709_pid_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(ii02709_pid STATIC IMPORTED)
set_target_properties(ii02709_pid PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../src/build/libii02709_pid.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/../src"
)

add_executable(ii02709_tests test_pid.cpp)

target_link_libraries(ii02709_tests
    PRIVATE
        ii02709_pid
        gtest
        gtest_main
)

if(ENABLE_COVERAGE_II02709)
    target_compile_options(ii02709_tests PRIVATE --coverage)
    target_link_options(ii02709_tests PRIVATE --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(ii02709_tests)

add_custom_target(coverage
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR}/.. --html --html-details -o coverage.html
)
