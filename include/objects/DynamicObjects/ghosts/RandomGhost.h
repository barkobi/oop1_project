#pragma once

#include "Ghost.h"

class RandomGhost : public Ghost{
public:
    RandomGhost(sf::Vector2f position, float scaleFactor);

    virtual void move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes);
private:
    Direction_t m_lastDirection;
};