cmake_minimum_required(VERSION 3.23)
project(project)

set(CMAKE_CXX_STANDARD 23)

set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

find_package(tinyxml2)

add_executable(project main.cpp
        src/gui/main_menu_screen.cpp
        src/gui/main_menu_screen.h
        src/system/common.h
        src/gui/button.cpp
        src/gui/button.h
        src/system/asset_loader.cpp
        src/system/asset_loader.h
        src/system/common.cpp
        src/game/level.cpp
        src/game/level.h
        src/game/ships.cpp
        src/game/ships.h
        src/gui/animation.cpp
        src/gui/animation.h
        src/game/game_data.h
        src/game/projectile.cpp
        src/game/projectile.h
        src/system/collidable.cpp
        src/system/collidable.h
        src/system/context.h
        src/system/sound_engine.cpp
        src/system/sound_engine.h
        src/gui/screen.cpp
        src/gui/screen.h
        src/gui/auxiliary_screens.cpp
        src/gui/auxiliary_screens.h
        src/game/hp_bar.cpp
        src/game/hp_bar.h
        src/game/visual_effect.cpp
        src/game/visual_effect.h
        src/game/enemy_ais.cpp
        src/game/enemy_ais.h)
target_link_libraries(project sfml-graphics sfml-window sfml-system sfml-audio tinyxml2)
target_compile_options(project PUBLIC -Wall -Werror)


