project(Parabox)

add_library(canvas STATIC canvas.cpp)

target_include_directories(canvas PUBLIC ${CMAKE_SOURCE_DIR}/include)
