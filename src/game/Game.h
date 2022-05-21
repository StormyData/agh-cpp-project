#pragma once

#include <vector>
#include "Level.h"
#include "GameData.h"

enum GameResult{WON, FAILED, EXITED};

class Game: public sf::Drawable
{
public:
    Game(std::vector<LevelData> level_data, const AssetLoader& assetLoader): levels(std::move(level_data)), assetLoader(assetLoader){};
    GameResult run_game();
    GameResult run_level(int level_no);
private:
    std::vector<LevelData> levels;
    const AssetLoader& assetLoader;
};