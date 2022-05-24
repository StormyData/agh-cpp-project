#include <optional>
#include "Game.h"
#include "GameData.h"

GameResult Game::run_game() {
    for(size_t i=0;i<context.assetLoader.get_levels().size();i++)
    {
        switch (run_level(i)) {
            case EXITED:
                return EXITED;
            case WON:
                continue;
            case FAILED:
                return FAILED;
        }
    }
    return WON;
}

GameResult Game::run_level(int level_no) {
    Level level = Level(context.assetLoader.get_levels()[level_no], context);
    std::optional<int> ret = level.run(player_health);
    if(!ret.has_value())
        return EXITED;
    player_health = ret.value();
    if(player_health > 0)
        return WON;
    return FAILED;
}
