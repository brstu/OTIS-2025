enable_testing()

find_package(GTest REQUIRED)

add_executable(pid_tests
    test_pid.cpp
)

target_link_libraries(pid_tests
    PRIVATE pid
    PRIVATE GTest::gtest
    PRIVATE GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(pid_tests)