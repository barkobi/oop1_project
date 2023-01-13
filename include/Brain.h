#pragma once

#include "DynamicObject.h"
#include <limits>
#include <queue>
namespace Brain{
    std::vector<std::vector<int>> calculateBFS(std::vector<std::string> map);

    std::vector<std::string> addObjectsToMap(std::vector<std::unique_ptr<DynamicObject>> *objects , std::vector<std::string> map, float tileSize,sf::Vector2f topLeft);
}