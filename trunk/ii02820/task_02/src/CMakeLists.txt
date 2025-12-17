cmake_minimum_required(VERSION 3.25)
project(ii02820_task02)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ТЕКУЩАЯ ПАПКА (src)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# ПАПКА НА УРОВЕНЬ ВЫШЕ (task_02)
set(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(ii02820_task02_main_program 
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/functions.cpp
)

add_executable(ii02820_task02_tests
    ${PARENT_DIR}/test/test_functions.cpp
    ${SRC_DIR}/functions.cpp
)

target_include_directories(ii02820_task02_tests PRIVATE
    ${SRC_DIR}
    ${PARENT_DIR}/test
)

target_link_libraries(
    ii02820_task02_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ii02820_task02_tests)