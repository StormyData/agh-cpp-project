#include <optional>
#include "Game.h"
#include "GameData.h"
#include "../gui/auxilary_screens.h"
#include "../gui/MainMenuScreen.h"

GameResult Game::run_level(size_t level_no) {
    Level level = Level(context.assetLoader.get_levels()[level_no], context);
    std::optional<int> ret = level.run(player_health);
    if(!ret.has_value())
        return EXITED;
    player_health = ret.value();
    if(player_health > 0)
        return WON;
    return FAILED;
}

Screen *Game::run() {
    for(size_t i=0;i<context.assetLoader.get_levels().size();i++)
    {
        switch (run_level(i)) {
            case EXITED:
                return nullptr;
            case WON:
                continue;
            case FAILED:
                Screen* main = new MainMenuScreen(context);
                displayText dt;
                dt.text = "Victory!!!";
                dt.style = 0;
                dt.size = 5;
                return new TimedTextScreen(context,dt, 5, "main_menu_background", main);
        }
    }
    Screen* main = new MainMenuScreen(context);
    displayText dt;
    dt.text = "Defeat!!!";
    dt.style = 0;
    dt.size = 5;
    return new TimedTextScreen(context,dt, 5, "main_menu_background", main);
}
