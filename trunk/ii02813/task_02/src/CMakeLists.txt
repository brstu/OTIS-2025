cmake_minimum_required(VERSION 3.14)
project(labubu2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


set(MODEL_SOURCES
    src/factory/factorylinearmodel.cpp
    src/factory/factorynonlinearmodel.cpp
    src/factory/ifactorymodel.cpp
    src/model/linearmodel.cpp
    src/model/nonlinearmodel.cpp
    src/model/isimulatedmodel.cpp
)


add_library(model_lib STATIC ${MODEL_SOURCES})


target_include_directories(model_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)


add_executable(main_app mainbubu.cpp)
target_include_directories(main_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(main_app model_lib)


add_executable(test_app test/testbubu.cpp)
target_include_directories(test_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(test_app model_lib GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(test_app)