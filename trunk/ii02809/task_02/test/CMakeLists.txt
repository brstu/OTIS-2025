cmake_minimum_required(VERSION 3.5)
project(task_02_ii02809_test)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(BUILD_GMOCK OFF CACHE BOOL "Disable building GoogleMock" FORCE)
set(BUILD_GTEST ON CACHE BOOL "Enable building GoogleTest" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(
  ${CMAKE_PROJECT_NAME}
  testFunctions.cpp

  ../src/functions.cpp

)
target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  PRIVATE
  gtest
  gtest_main
)


target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE --coverage -g -O0)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE --coverage)


include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME})