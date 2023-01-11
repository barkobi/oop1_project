#pragma once

#include "StaticObject.h"
#include "Pacman.h"
#include "Ghost.h"


class Wall : public StaticObject{
public:
    Wall(sf::Texture *texture, sf::Vector2f position, float scaleFactor);

    void handleCollision(GameObject& object) { object.handleCollision(*this); }
    void handleCollision(Pacman& pacman) { pacman.handleCollision(*this); }
    void handleCollision(Ghost& ghost) { ghost.handleCollision(*this); }
    virtual int checkDistance(const sf::Vector2f& pos){return WINDOW_WIDTH;}
private:
};
