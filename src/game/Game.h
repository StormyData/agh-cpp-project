#pragma once

#include <vector>
#include "Level.h"
#include "GameData.h"
#include "../system/context.h"
enum GameResult{WON, FAILED, EXITED};

class Game: public sf::Drawable
{
public:
    Game(Context& context): context(context) {};
    GameResult run_game();
    GameResult run_level(int level_no);
private:
    Context& context;
    int player_health;
};