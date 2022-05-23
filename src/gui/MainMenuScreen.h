#pragma once
#include <SFML/Graphics.hpp>
#include "../system/context.h"

class MainMenuScreen
{
    Context& context;
public:
    explicit MainMenuScreen(Context& context) : context(context) {}
    void run();

};