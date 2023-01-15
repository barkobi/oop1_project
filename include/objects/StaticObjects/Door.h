#pragma once

#include "StaticObject.h"
#include "objects/DynamicObjects/ghosts/Ghost.h"
#include "Pacman.h"
class Door : public StaticObject{

public:
    Door(sf::Vector2f position, float scaleFactor);

    void handleCollision(GameObject& object) { object.handleCollision(*this); }
    void handleCollision(Pacman& player) { player.handleCollision(*this); }
    void handleCollision(Ghost& gameObject) { gameObject.handleCollision(*this); }
    virtual float checkDistance(const sf::Vector2f& pos);
    virtual void animation() {}
};