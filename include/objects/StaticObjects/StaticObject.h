#pragma once
#include "objects/GameObject.h"

class StaticObject : public GameObject{
public:
    StaticObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
private:
};
