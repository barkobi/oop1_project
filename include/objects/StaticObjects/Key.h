#pragma once

#include "StaticObject.h"
#include "objects/DynamicObjects/ghosts/Ghost.h"
#include "Pacman.h"

/**
 * Key class heiress from static objects
 */
class Key : public StaticObject{
public:
    // C-Tor
    Key(sf::Vector2f position, float scaleFactor,float tileSize);

    // Functions
    void handleCollision(GameObject& object) { object.handleCollision(*this); }
    void handleCollision(Pacman& player) { player.handleCollision(*this); }
    void handleCollision(Ghost& gameObject) { gameObject.handleCollision(*this); }
    virtual float checkDistance(const sf::Vector2f& pos){return WINDOW_WIDTH;}
    virtual void animation() {}
};
