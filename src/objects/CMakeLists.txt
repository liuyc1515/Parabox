project(Parabox)

add_library(objects STATIC base_object.cpp wall_object.cpp player_object.cpp block_object.cpp void_object.cpp)

target_include_directories(objects PUBLIC ${CMAKE_SOURCE_DIR}/include)