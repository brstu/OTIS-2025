cmake_minimum_required(VERSION 3.5)
project(task_02_ii02720_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable code coverage flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Create test executable
add_executable(
  ${CMAKE_PROJECT_NAME}
  test.cpp

  ../src/model/isimulatedmodel.h
  ../src/model/linearmodel.h
  ../src/model/nonlinearmodel.h
  ../src/factory/ifactorymodel.h
  ../src/factory/factorylinearmodel.h
  ../src/factory/factorynonlinearmodel.h
)

# Link Google Test libraries
target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  PRIVATE
  gtest
  gtest_main
  gmock
)

# Add coverage flags
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE --coverage -g -O0)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE --coverage)

# Discover tests
include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME})

