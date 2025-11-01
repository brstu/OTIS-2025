cmake_minimum_required(VERSION 3.5)
project(task_02_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME}
    test.cpp
    ../src/model/linearmodel.h
    ../src/model/nonlinearmodel.h
    ../src/factory/ifactorymodel.h
    ../src/factory/factorylinearmodel.h
    ../src/factory/factorynonlinearmodel.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main gmock)
target_compile_options(${PROJECT_NAME} PRIVATE --coverage -g -O0)
target_link_options(${PROJECT_NAME} PRIVATE --coverage)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
