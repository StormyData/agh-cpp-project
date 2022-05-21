#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "../system/AssetLoader.h"
#include "GameData.h"
class Ship;

class Level : public sf::Drawable{
public:
    explicit Level(const LevelData& data, const AssetLoader& assetLoader)
    {

    }
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    sf::Sprite background;
    std::list<Ship*> ships;

};

