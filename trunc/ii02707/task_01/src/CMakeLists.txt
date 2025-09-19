cmake_minimum_required (VERSION 3.5)
project (task_01_ii02707)

set(EXECUTABLE_NAME
    output
)
set(PROJECT_SOURCES
    main.cpp
)
set(EXECUTABLE_OUTPUT_PATH
    ${PROJECT_NAME}/trunc/ii2707/task01
)

add_executable (${EXECUTABLE_NAME} ${SOURCE_FILES})