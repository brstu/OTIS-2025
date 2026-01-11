# Только здесь создаем testlab3_runner_ii02820
add_executable(testlab3_runner_ii02820 test_model.cpp)

target_link_libraries(testlab3_runner_ii02820
    PRIVATE
    model_lib
    gtest
    gtest_main
)

target_include_directories(testlab3_runner_ii02820
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

include(GoogleTest)
gtest_discover_tests(testlab3_runner_ii02820)