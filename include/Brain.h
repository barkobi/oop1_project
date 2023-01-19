#pragma once

#include "DynamicObject.h"
#include <limits>
#include <queue>
#include "GameBoard.h"

namespace Brain{
    std::vector<std::vector<int>> calculateBFS(std::vector<std::string> map);

    std::vector<std::string> addObjectsToMap(sf::Vector2f pacloc, std::vector<std::string> map, float tileSize, sf::Vector2f topLeft,float pacSize);

    sf::Vector2i calcMyTile(sf::Vector2f location, Bounds bounds,float size);
}