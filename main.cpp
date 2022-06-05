#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "src/gui/MainMenuScreen.h"
#include "src/system/context.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "OUT OF SPACE");
    Context context(window);
    Screen* screen = new MainMenuScreen(context);
    while (screen != nullptr)
    {
        screen = screen->run();
    }
    window.close();
    return 0;
}
