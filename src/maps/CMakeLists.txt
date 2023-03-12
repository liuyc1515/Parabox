project(Parabox)

add_subdirectory(static_maps)
add_subdirectory(inner_map_maps)

add_library(maps STATIC base_map.cpp)

target_include_directories(maps PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(maps PRIVATE static_maps inner_map_maps)