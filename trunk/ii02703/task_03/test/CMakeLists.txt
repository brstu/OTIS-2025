set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(pid_tests
    pid_tests.cpp
)

target_link_libraries(pid_tests
    gtest_main
    pid_lib
)

enable_testing()
add_test(NAME pid_tests COMMAND pid_tests)
