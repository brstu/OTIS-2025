
add_library(model_lib
    model.cpp
    model.h
)


add_executable(main_program
    main.cpp
)


target_link_libraries(main_program model_lib)

target_include_directories(model_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(main_program PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})