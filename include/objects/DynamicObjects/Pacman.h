#pragma once

#include "DynamicObject.h"
#include "eventLoop.h"

class Pacman : public DynamicObject{
public:
    Pacman(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
    void move(float deltaTime, Bounds boardBounds, std::vector<std::vector<int>> bfsRes);

    virtual void handleCollision(GameObject&);
    virtual void handleCollision(Pacman&);
    virtual void handleCollision(Ghost& ghost);
    virtual void handleCollision(Key&);
    virtual void handleCollision(Door&);
    virtual void handleCollision(Cookie&);
    virtual void handleCollision(Gift&);
    virtual void handleCollision(Wall& wall);
    virtual void updateAnimation();

private:
    int m_rect;

};


