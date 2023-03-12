project(Parabox)

add_library(agents STATIC base_agent.cpp inner_map_agent.cpp recursion_agent.cpp)

target_include_directories(agents PUBLIC ${CMAKE_SOURCE_DIR}/include)
