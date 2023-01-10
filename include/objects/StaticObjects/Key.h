#pragma once

#include "StaticObject.h"
#include "Ghost.h"
#include "Pacman.h"
class Key : public StaticObject{
public:
    Key(sf::Texture *texture, sf::Vector2f position, float scaleFactor);

    void handleCollision(GameObject& object) { object.handleCollision(*this); }
    void handleCollision(Pacman& player) { player.handleCollision(*this); }
    void handleCollision(Ghost& gameObject) { gameObject.handleCollision(*this); }
    virtual int checkDistance(sf::Vector2f& pos){return WINDOW_WIDTH;}
};
