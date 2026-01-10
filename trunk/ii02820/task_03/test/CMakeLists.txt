cmake_minimum_required(VERSION 3.5)
project(testlab3_tests_ii02820)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги coverage
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тестовый бинарник - ТОЛЬКО тесты и нужные модули БЕЗ main()
add_executable(
    ${CMAKE_PROJECT_NAME}
    test_model.cpp
    ../src/lin_model.cpp  # ТОЛЬКО lin_model
    # НЕ добавляем model_validation.cpp если там есть main()
)

# Include директории
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    ../src
)

# Ссылки на библиотеки
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    gtest
    gtest_main  # gtest_main предоставляет свою main()
)

# Дополнительные флаги coverage
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE --coverage -g -O0)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE --coverage)
endif()

# Google Test интеграция
include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME})