cmake_minimum_required(VERSION 3.10)
project(GraphVisualizer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(raylib REQUIRED) 

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "main.cpp")

add_executable(GraphSolver ${SOURCES})

target_link_libraries(GraphSolver PRIVATE 
    raylib 
    Threads::Threads
)
