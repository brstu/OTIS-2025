cmake_minimum_required(VERSION 3.16)
project(ii02709_task_03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# опция запуска тестов/покрытия
option(ENABLE_COVERAGE_II02709 "Enable coverage flags" OFF)

if(ENABLE_COVERAGE_II02709)
  message(STATUS "Coverage build enabled (ii02709)")
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
  endif()
  add_compile_options(--coverage -O0 -g)
  add_link_options(--coverage)
endif()

add_subdirectory(src)
add_subdirectory(test)
