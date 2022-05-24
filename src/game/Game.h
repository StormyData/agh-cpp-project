#pragma once

#include <vector>
#include "Level.h"
#include "GameData.h"
#include "../system/context.h"
#include "../gui/Screen.h"
enum GameResult{WON, FAILED, EXITED};

class Game: public Screen
{
public:
    Game(Context& context): Screen(context, false) {};
    GameResult run_level(size_t level_no);
    bool process_additional_event(sf::Event &) override;
    bool update_logic(float) override;
    void on_exit() override;
    Screen* run() override;
private:
    int player_health;
};