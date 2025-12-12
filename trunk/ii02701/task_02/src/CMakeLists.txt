file(GLOB SRC_FILES "*.cpp")
add_library(task02_lib STATIC ${SRC_FILES})
target_include_directories(task02_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})