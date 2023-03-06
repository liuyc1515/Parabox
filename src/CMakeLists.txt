project(Parabox)

add_subdirectory(agents)
add_subdirectory(canvas)
add_subdirectory(keyboard)
add_subdirectory(utils)
add_subdirectory(objects)
add_subdirectory(maps)
add_subdirectory(manager)

add_library(game STATIC parabox.cpp)

target_include_directories(game PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(game PRIVATE agents canvas keyboard utils objects maps manager)