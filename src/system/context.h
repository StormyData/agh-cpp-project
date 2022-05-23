//
// Created by tobiasz on 23.05.2022.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "AssetLoader.h"

struct Context
{
    sf::RenderWindow& window;
    AssetLoader assetLoader;
};