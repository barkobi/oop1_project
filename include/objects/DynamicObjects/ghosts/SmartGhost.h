#pragma once

#include "Ghost.h"

class SmartGhost : public Ghost{
public:
    SmartGhost(sf::Vector2f position, float scaleFactor);

    virtual void move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes);

private:
    Direction_t m_lastDirection;
};
