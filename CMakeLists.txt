cmake_minimum_required(VERSION 3.23)
project(project)

set(CMAKE_CXX_STANDARD 23)

set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

add_executable(project main.cpp src/main_menu.cpp src/main_menu.h src/common.h src/Button.cpp src/Button.h src/AssetLoader.cpp src/AssetLoader.h src/common.cpp src/game.cpp src/game.h src/level.cpp src/level.h)
target_link_libraries(project sfml-graphics sfml-window sfml-system sfml-audio)
