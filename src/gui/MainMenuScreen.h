#pragma once
#include <SFML/Graphics.hpp>

class MainMenuScreen
{
    sf::RenderWindow& _window;
public:
    explicit MainMenuScreen(sf::RenderWindow& window) : _window(window)
    {

    }
    void run();

};