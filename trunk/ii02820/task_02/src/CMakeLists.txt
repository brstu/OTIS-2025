cmake_minimum_required(VERSION 3.25)
project(ii02820_task02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE  
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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

target_link_libraries(
  runTests_ii02820
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTests_ii02820)