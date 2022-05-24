#include <optional>
#include "Level.h"
#include "Ship.h"

std::optional<int> Level::run(int initial_player_health) {
    ships.clear();
    projectiles.clear();
    background.setTexture(context.assetLoader.get_texture(data.background),true);
    for(const auto& ship_blueprint : data.ships)
        ships.push_back(new Ship(ship_blueprint, context.assetLoader));
    size_t n_of_enemies = data.ships.size();
    PlayerShip* playerShip = nullptr;
    ships.push_back(playerShip);
    sf::Clock clock1;
    while (n_of_enemies > 0 && context.window.isOpen())
    {
        //float elapsed = (float)clock1.getElapsedTime().asMicroseconds() / 1000000.0f;
        clock1.restart();
        sf::Event event{};
        while (context.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                context.window.close();
            } else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    return {};
                }
            }
        }

        context.window.clear();
        context.window.draw(background);
        for(Projectile* p : projectiles)
        {
            context.window.draw(*p);
        }
        for(Ship* p : ships)
        {
            context.window.draw(*p);
        }
        context.window.display();
    }
    return 0;
}
