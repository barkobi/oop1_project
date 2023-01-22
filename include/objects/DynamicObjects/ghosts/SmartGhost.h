#pragma once

#include "Ghost.h"
#include <cmath>

/**
 * smart ghost class heiress from ghost class
 */
class SmartGhost : public Ghost{
public:
    // C-tor
    SmartGhost(sf::Vector2f position, float scaleFactor,float tileSize);

    // move function
    virtual void move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes);

private:
    // members
    sf::Clock m_collisionClock;
    sf::Vector2i m_myLocation;
    bool m_blocked = false;

    // private functions
    void calcMyLocation(Bounds boardBounds);

};
