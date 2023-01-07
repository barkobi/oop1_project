#pragma once

#include "DynamicObject.h"

class Pacman : public DynamicObject{
public:
    Pacman(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
    void move(float deltaTime);

    virtual void handleCollision(GameObject&);
    virtual void handleCollision(Pacman&);
    virtual void handleCollision(Ghost&);
    virtual void handleCollision(Key&);
    virtual void handleCollision(Door&);
    virtual void handleCollision(Cookie&);
    virtual void handleCollision(Gift&);
    virtual void handleCollision(Wall&);
private:

};


