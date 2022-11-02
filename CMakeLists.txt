cmake_minimum_required(VERSION 3.25)

project(MazeVisualizer)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics window system audio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

file(GLOB_RECURSE SRC
"MazeVisualizer/src/*.h"
"MazeVisualizer/src/*.cpp"
)

add_executable(
 ${PROJECT_NAME}
 ${SRC}
)

target_link_libraries(
 ${PROJECT_NAME}

 sfml-graphics
 sfml-window
 sfml-system
 sfml-audio
)
