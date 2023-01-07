#pragma once

#include "StaticObject.h"

class Cookie : public StaticObject{
public:
    Cookie(sf::Texture *texture, sf::Vector2f position, float scaleFactor);

    void handleCollision(GameObject& object) { object.handleCollision(*this); }
//    void handleCollision(Pacman& player) { player.handleCollision(*this); }
//    void handleCollision(Ghost& gameObject) { gameObject.handleCollision(*this); }
};
