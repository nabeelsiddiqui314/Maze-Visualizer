cmake_minimum_required(VERSION 3.25)

project(MazeVisualizer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)

find_package(SFGUI REQUIRED)

include_directories(${SFGUI_INCLUDE_DIR})

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

set(SFML_LIBS 
 sfml-graphics
 sfml-window
 sfml-system
 sfml-audio
)

target_link_libraries(
 ${PROJECT_NAME}
 ${SFML_LIBS}
 ${SFGUI_LIBRARY}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
)

get_filename_component(SFGUI_DIR ${SFGUI_INCLUDE_DIR} DIRECTORY)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${SFGUI_DIR}/bin" $<TARGET_FILE_DIR:${PROJECT_NAME}>
)