#pragma once

#include "DynamicObject.h"

class Pacman : public DynamicObject{
public:
    Pacman(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
    virtual void move(GameObject &other);

private:

};


