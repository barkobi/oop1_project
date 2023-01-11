#include <cmath>
#include "objects/StaticObjects/Door.h"

Door::Door(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : StaticObject(texture, position, scaleFactor){}

int Door::checkDistance(const sf::Vector2f &pos) {
    auto dorpos = this->getSprite().getPosition();
    return sqrt(pow(pos.x - dorpos.x, 2) + pow(pos.y - dorpos.y, 2) * 1.0);
}
