//
// Created by tobiasz on 09.05.2022.
//

#include "main_menu.h"
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "AssetLoader.h"

void MainMenuScreen::run() {

    AssetLoader assetLoader;
    sf::Sprite background_sprite(assetLoader.get_texture("main_menu_background"));
    bool goto_game = false;
    ButtonProperties start_button_properties;
    start_button_properties.text = "start game";
    start_button_properties.where = sf::FloatRect(0, 0, 800, 600);
    start_button_properties.v_align = start_button_properties.h_align = Alignment::CENTER;
    start_button_properties.onClick = [&goto_game](){ goto_game = true;};
    Button start_button(start_button_properties, assetLoader);
    bool redraw_required = true;

    while (_window.isOpen())
    {
        sf::Event event{};
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                start_button.test_click(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y));
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                redraw_required |= start_button.test_mouseover(sf::Vector2f(sf::Mouse::getPosition(_window)));
            }
        }

        if(goto_game)
        {
            std::cout<< "gone to game, and returned from game\n";
            goto_game = false;
        }

        if(!redraw_required)
            continue;
        _window.clear();
        _window.draw(background_sprite);
        _window.draw(start_button);
        _window.display();
        redraw_required = false;
    }
}
