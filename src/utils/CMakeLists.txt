project(Parabox)

add_library(utils STATIC utils.cpp)

target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include)