//
// Created by tobiasz on 09.05.2022.
//

#include "MainMenuScreen.h"
#include <SFML/Graphics.hpp>
#include "../system/AssetLoader.h"
#include "Button.h"

void MainMenuScreen::run() {

    sf::Sprite background_sprite(context.assetLoader.get_texture("main_menu_background"));
    bool goto_game = false;
    ButtonProperties start_button_properties;
    start_button_properties.text = "start game";
    start_button_properties.where = sf::FloatRect(0, 0, 800, 600);
    start_button_properties.v_align = start_button_properties.h_align = Alignment::CENTER;
    start_button_properties.onClick = [&goto_game](){ goto_game = true;};
    Button start_button(start_button_properties, context.assetLoader);
    bool redraw_required = true;

    Animation enemy1(context.assetLoader.get_animation("enemy_1"));

    sf::Clock clock1;
    while (context.window.isOpen())
    {
        float elapsed = (float)clock1.getElapsedTime().asMicroseconds() / 1000000.0f;
        clock1.restart();
        sf::Event event{};
        while (context.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                context.window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                start_button.test_click(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y));
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                redraw_required |= start_button.test_mouseover(sf::Vector2f(sf::Mouse::getPosition(context.window)));
            }
        }
        if(goto_game)
        {
            std::cout<< "gone to game, and returned from game\n";
            goto_game = false;
        }
        redraw_required |= enemy1.update(elapsed);

        if(!redraw_required)
            continue;
        context.window.clear();
        context.window.draw(background_sprite);
        context.window.draw(start_button);
        context.window.draw(enemy1);
        context.window.display();
        redraw_required = false;
//        while (clock1.getElapsedTime().asMilliseconds() < 1000/60);

    }
}
