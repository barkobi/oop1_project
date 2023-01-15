#pragma once

#include "Gift.h"

class TimeAddGift : public Gift{
public:
    TimeAddGift(sf::Vector2f position, float scaleFactor);
    void handleCollision(GameObject& object) { object.handleCollision(*this); }
    void handleCollision(Pacman& player) { player.handleCollision(*this); }
    void handleCollision(Ghost& gameObject) { gameObject.handleCollision(*this); }
private:

};