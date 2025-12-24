add_library(task02_lib
    model.cpp
)

target_include_directories(task02_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_executable(task02_app main.cpp)
target_link_libraries(task02_app PRIVATE task02_lib)