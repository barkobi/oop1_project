#pragma once

#include "Gift.h"

/**
 * TimeAddGift class heiress from Gift class
 */
class TimeAddGift : public Gift{
public:
    //C-Tor
    TimeAddGift(sf::Vector2f position, float scaleFactor,float tileSize);
    // Double Dispatch
    void handleCollision(GameObject& object) { object.handleCollision(*this); }
    void handleCollision(Pacman& player) { player.handleCollision(*this); }
    void handleCollision(Ghost& gameObject) { gameObject.handleCollision(*this); }
private:

};