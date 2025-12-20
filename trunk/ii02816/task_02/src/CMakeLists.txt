cmake_minimum_required(VERSION 3.15)
project(task_02_ii02816_src CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SRC
    main.cpp
    l.h
    nonl.h
)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_test 
    ../test/test.cpp
    nonl.h
    l.h
)
target_link_libraries(${PROJECT_NAME}_test 
    PRIVATE 
    gtest 
    gtest_main 
    gmock
)

enable_testing()
add_test(NAME ${PROJECT_NAME}_tests 
    COMMAND ${PROJECT_NAME}_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)