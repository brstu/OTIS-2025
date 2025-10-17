cmake_minimum_required (VERSION 3.5)
project(task_02_ii02707_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    main.cpp
    
    model/isimulatedmodel.h
    model/linearmodel.h
    model/nonlinearmodel.h
    factory/ifactorymodel.h
    factory/factorylinearmodel.h
    factory/factorynonlinearmodel.h
)

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})
