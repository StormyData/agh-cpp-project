#include "Level.h"
#include "Ship.h"

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(Ship* ship : ships)
        target.draw( *ship, states);

}
