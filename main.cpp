#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "src/gui/MainMenuScreen.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    MainMenuScreen menuScreen(window);
    menuScreen.run();
    return 0;
}
