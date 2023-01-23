#pragma once
#include "Gift.h"
/**
 * GhostFreezeGift class heiress from Gift class
 */
class GhostFreezeGift : public Gift{
public:
    // C-Tor
    GhostFreezeGift(sf::Vector2f position, float scaleFactor,float tileSize);
    // Double Dispatch.
    void handleCollision(GameObject& object) { object.handleCollision(*this); }
    void handleCollision(Pacman& player) { player.handleCollision(*this); }
    void handleCollision(Ghost& gameObject) { gameObject.handleCollision(*this); }

private:
};


