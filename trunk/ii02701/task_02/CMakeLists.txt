cmake_minimum_required(VERSION 3.20)
project(task_02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Building with coverage flags")
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

install(DIRECTORY doc
        DESTINATION .
        FILES_MATCHING PATTERN "*.md" PATTERN "*.pdf")

FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()