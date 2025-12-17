cmake_minimum_required(VERSION 3.25)
project(ii02820_task02)


if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(GTest QUIET)

if(NOT GTest_FOUND)
    
    message(STATUS "GTest not found, downloading via FetchContent...")
    
    include(FetchContent)
    
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

enable_testing()

add_executable(main_program 
    main.cpp
    functions.cpp
)

add_executable(runTests_ii02820
    ../test/test_functions.cpp
    functions.cpp
)

target_include_directories(runTests_ii02820 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../test
)

if(GTest_FOUND)
    target_link_libraries(
        runTests_ii02820
        GTest::gtest
        GTest::gtest_main
    )
else()
    target_link_libraries(
        runTests_ii02820
        GTest::gtest_main
    )
endif()

include(GoogleTest)
gtest_discover_tests(runTests_ii02820)