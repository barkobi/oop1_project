#pragma once
#include "objects/GameObject.h"

class StaticObject : public GameObject{
public:
    StaticObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
    virtual ~StaticObject() = default;


    virtual void handleCollision(GameObject&) = 0;
    virtual void handleCollision(Pacman&) {};
    virtual void handleCollision(Ghost&) {};
    virtual void handleCollision(Wall&){};
    virtual void handleCollision(Key&){};
    virtual void handleCollision(Door&){};
    virtual void handleCollision(Cookie&) {};
    virtual void handleCollision(Gift&) {};
private:
};
