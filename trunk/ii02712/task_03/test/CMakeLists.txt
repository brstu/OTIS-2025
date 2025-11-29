cmake_minimum_required(VERSION 3.5)
project(task_03_ii02712_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

set(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/../src/functions.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/functions.cpp
)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  gtest
  gtest_main
  gmock
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})