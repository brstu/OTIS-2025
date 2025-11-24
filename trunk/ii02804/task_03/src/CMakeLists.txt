cmake_minimum_required(VERSION 3.16)
project(task_03_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Исходники ----
set(SRC_FILES
    main.cpp
    pid.cpp
    models.cpp
)

set(HEADERS
    pid.h
    models.h
)

# ---- Библиотека core (PID + модели) ----
add_library(core ${SRC_FILES} ${HEADERS})
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ---- Исполняемый файл симулятора ----
add_executable(simulator main.cpp)
target_link_libraries(simulator PRIVATE core)
target_include_directories(simulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ---- Doxygen ----
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
  add_custom_target(docs
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/../Doxyfile
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/..
    COMMENT "Generating Doxygen documentation"
  )
endif()
