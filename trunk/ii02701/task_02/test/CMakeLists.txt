enable_testing()

add_executable(unit_tests
    test_model.cpp
)

target_link_libraries(unit_tests
    PRIVATE
        task02_lib
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME AllTests COMMAND $<TARGET_FILE:unit_tests>)
message(">>> REGISTERING UNIT TESTS <<<")