#pragma once

#include "Ghost.h"
#include <cmath>

class SmartGhost : public Ghost{
public:
    SmartGhost(sf::Vector2f position, float scaleFactor,float tileSize);

    virtual void move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes);

private:
    sf::Clock m_collisionClock;
    sf::Vector2i m_myLocation;
    bool m_blocked = false;

    void calcMyLocation(Bounds boardBounds);

};
