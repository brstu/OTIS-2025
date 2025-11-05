cmake_minimum_required (VERSION 3.5)
project(task_03_ii02707_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/model/isimulatedmodel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/linearmodel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/nonlinearmodel.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/factory/ifactorymodel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/factory/factorylinearmodel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/factory/factorynonlinearmodel.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/regulator/iregulator.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/regulator/pidregulator.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/adaptivecontroller.hpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})