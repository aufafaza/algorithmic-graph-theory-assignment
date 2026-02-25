cmake_minimum_required(VERSION 3.11)
project(GraphVisualizer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        5.0 
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

find_package(Threads REQUIRED)

file(GLOB SOURCES "src/*.cpp" "main.cpp")

add_executable(GraphSolver ${SOURCES})

target_include_directories(GraphSolver PRIVATE include)

target_link_libraries(GraphSolver PRIVATE 
    raylib 
    Threads::Threads
)

if(APPLE)
    target_link_libraries(GraphSolver PRIVATE
        "-framework CoreVideo"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework GLUT"
        "-framework OpenGL"
    )
elseif(UNIX)
    target_link_libraries(GraphSolver PRIVATE m pthread dl rt X11)
endif()
