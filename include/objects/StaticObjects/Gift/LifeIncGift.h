#pragma once

#include "Gift.h"

class LifeIncGift : public  Gift{
public:
    LifeIncGift(sf::Vector2f position, float scaleFactor);
    void handleCollision(GameObject& object) { object.handleCollision(*this); }
    void handleCollision(Pacman& player) { player.handleCollision(*this); }
    void handleCollision(Ghost& gameObject) { gameObject.handleCollision(*this); }
private:
};
