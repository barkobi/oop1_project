#include "objects/StaticObjects/StaticObject.h"

StaticObject::StaticObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : GameObject(texture,position,scaleFactor){}