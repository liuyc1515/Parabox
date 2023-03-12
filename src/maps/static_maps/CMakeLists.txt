project(Parabox)

add_library(static_maps STATIC base_static_map.cpp static_map_1.cpp static_map_2.cpp)

target_include_directories(static_maps PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(static_maps PUBLIC ${CMAKE_SOURCE_DIR}/include/maps)