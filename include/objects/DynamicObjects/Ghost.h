#pragma once
#include "DynamicObject.h"
class Ghost : public DynamicObject{
public:
    Ghost(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
    void move(float deltaTime, Bounds boardBounds);

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
