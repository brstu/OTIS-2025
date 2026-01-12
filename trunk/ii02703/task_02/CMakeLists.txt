cmake_minimum_required(VERSION 3.14)
project(Task02_UnitTests)

set(CMAKE_CXX_STANDARD 14)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

if(MSVC)
    add_compile_options(/W4)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fprofile-arcs -ftest-coverage")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_library(core_models src/models.cpp src/models.hpp)

add_executable(app_task02 src/main.cpp)
target_link_libraries(app_task02 PRIVATE core_models)

enable_testing()

add_executable(unit_tests test/tests.cpp)
target_link_libraries(unit_tests
    PRIVATE
    core_models
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)