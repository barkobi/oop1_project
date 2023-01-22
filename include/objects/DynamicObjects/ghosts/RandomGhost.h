#pragma once

#include "Ghost.h"

/**
 * random ghost class heiress from Ghost
 */
class RandomGhost : public Ghost{
public:
    // random ghost C-tor
    RandomGhost(sf::Vector2f position, float scaleFactor,float tileSize);

    // move function
    virtual void move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes);
private:
    // which direction
    Direction_t m_lastDirection;
};
