project(Parabox)

add_library(manager STATIC map_manager.cpp object_manager.cpp)

target_include_directories(manager PUBLIC ${CMAKE_SOURCE_DIR}/include)
