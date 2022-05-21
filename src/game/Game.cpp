#include "Game.h"
#include "GameData.h"

GameResult Game::run_game() {
    for(int i=0;i<levels.size();i++)
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
    Level level = Level(levels[level_no], assetLoader);
    return FAILED;
}
