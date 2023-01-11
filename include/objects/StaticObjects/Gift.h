#pragma once

#include "StaticObject.h"
#include "Ghost.h"
#include "Pacman.h"

class Gift : public StaticObject{
public:
    Gift(sf::Texture *texture, sf::Vector2f position, float scaleFactor);

    void handleCollision(GameObject& object) { object.handleCollision(*this); }
    void handleCollision(Pacman& player) { player.handleCollision(*this); }
    void handleCollision(Ghost& gameObject) { gameObject.handleCollision(*this); }
    virtual void animation() {}
    virtual float checkDistance(const sf::Vector2f& pos){return WINDOW_WIDTH;}
private:
};