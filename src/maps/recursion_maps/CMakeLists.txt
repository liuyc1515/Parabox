project(Parabox)

add_library(recursion_maps STATIC base_recursion_map.cpp recursion_map1.cpp)

target_include_directories(recursion_maps PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(recursion_maps PUBLIC ${CMAKE_SOURCE_DIR}/include/maps)