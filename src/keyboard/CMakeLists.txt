project(Parabox)

add_library(keyboard STATIC keyboard_control.cpp)

target_include_directories(keyboard PUBLIC ${CMAKE_SOURCE_DIR}/include)