//
// Created by tobiasz on 17.05.2022.
//

#pragma once

#include "GameData.h"
#include "../system/AssetLoader.h"

class Ship : public sf::Drawable
{
public:
    Ship(const ShipData& shipData, const AssetLoader& assetLoader);
};


