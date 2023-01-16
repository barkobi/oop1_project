#pragma once

#include "Gift.h"

class SuperPacGift : public  Gift{
public:
    SuperPacGift(sf::Vector2f position, float scaleFactor,float tileSize);
    void handleCollision(GameObject& object) { object.handleCollision(*this); }
    void handleCollision(Pacman& player) { player.handleCollision(*this); }
    void handleCollision(Ghost& gameObject) { gameObject.handleCollision(*this); }
private:

};
