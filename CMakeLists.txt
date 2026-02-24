cmake_minimum_required(VERSION 3.10)
project(GraphVisualizer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(raylib REQUIRED) 

file(GLOB SOURCES "src/*.cpp" "main.cpp")

add_executable(GraphSolver src/Graph.cpp main.cpp)
target_link_libraries(GraphSolver raylib) 


