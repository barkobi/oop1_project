#pragma once

#include "DynamicObject.h"
class Ghost : public DynamicObject{
public:
    Ghost(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
    virtual void move(GameObject &other);
private:

};
