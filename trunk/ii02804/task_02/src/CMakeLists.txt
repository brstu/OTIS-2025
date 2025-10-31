cmake_minimum_required(VERSION 3.5)
project(task_02_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    main.cpp
    model/linearmodel.h
    model/nonlinearmodel.h
    factory/ifactorymodel.h
    factory/factorylinearmodel.h
    factory/factorynonlinearmodel.h
)
