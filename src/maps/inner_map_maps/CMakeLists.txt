project(Parabox)

add_library(inner_map_maps STATIC base_inner_map_map.cpp inner_map_map1.cpp)

target_include_directories(inner_map_maps PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(inner_map_maps PUBLIC ${CMAKE_SOURCE_DIR}/include/maps)