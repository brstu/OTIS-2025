cmake_minimum_required(VERSION 3.5)
project(task_03_ii02707_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

set(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/../src/model/linearmodel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/model/nonlinearmodel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/model/isimulatedmodel.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/../src/factory/factorylinearmodel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/factory/factorynonlinearmodel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/factory/ifactorymodel.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/../src/regulator/pidregulator.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/regulator/iregulator.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/../src/adaptivecontroller.hpp
)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  gtest
  gtest_main
  gmock
)
target_compile_options(${PROJECT_NAME} PRIVATE --coverage -g -O0)
target_link_options(${PROJECT_NAME} PRIVATE --coverage)


include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})