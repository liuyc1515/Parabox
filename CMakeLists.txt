cmake_minimum_required(VERSION 3.5)

project(Parabox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

add_executable(Parabox main.cpp)

target_link_libraries(Parabox game)
