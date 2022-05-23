cmake_minimum_required(VERSION 3.23)
project(project)

set(CMAKE_CXX_STANDARD 23)

set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

find_package(tinyxml2)

add_executable(project main.cpp src/gui/MainMenuScreen.cpp src/gui/MainMenuScreen.h src/system/common.h src/gui/Button.cpp src/gui/Button.h src/system/AssetLoader.cpp src/system/AssetLoader.h src/system/common.cpp src/game/Game.cpp src/game/Game.h src/game/Level.cpp src/game/Level.h src/game/Ship.cpp src/game/Ship.h src/gui/Animation.cpp src/gui/Animation.h src/game/GameData.cpp src/game/GameData.h src/game/Projectile.cpp src/game/Projectile.h src/system/Collidable.cpp src/system/Collidable.h src/system/context.h src/system/SoundEngine.cpp src/system/SoundEngine.h)
target_link_libraries(project sfml-graphics sfml-window sfml-system sfml-audio tinyxml2)
