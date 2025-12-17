cmake_minimum_required(VERSION 3.14)
project(ModelLab)

set(CMAKE_CXX_STANDARD 17)

add_executable(model_app src/main.cpp src/model.cpp)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(model_tests test/test_model.cpp src/model.cpp)
target_link_libraries(model_tests PRIVATE gtest_main)
target_include_directories(model_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(model_tests)