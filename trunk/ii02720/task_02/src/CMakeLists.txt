cmake_minimum_required(VERSION 3.14)
project(task_02_ii02720_src)

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

add_executable(task_02_ii02720 ${PROJECT_SOURCES})
