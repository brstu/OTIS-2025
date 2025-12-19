cmake_minimum_required(VERSION 3.5)
project(task_03_ii02720)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    main.cpp
    model/isimulatedmodel.hpp
    model/linearmodel.hpp
    model/nonlinearmodel.hpp
    factory/ifactorymodel.hpp
    factory/factorylinearmodel.hpp
    factory/factorynonlinearmodel.hpp
    regulator/iregulator.hpp
    regulator/pidregulator.hpp
    adaptivecontroller.hpp
)
