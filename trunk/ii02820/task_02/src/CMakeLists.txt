cmake_minimum_required(VERSION 3.25)
project(ii02820_task02)

# Fix timestamp warning
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Main executable
add_executable(model_app
    main.cpp
    model.cpp
)

# Test executable
add_executable(model_tests
    ../test/test_model.cpp
    model.cpp
)

target_include_directories(model_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    model_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(model_tests)