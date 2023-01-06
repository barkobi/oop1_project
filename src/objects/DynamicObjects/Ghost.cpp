#include "Ghost.h"

Ghost::Ghost(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : DynamicObject(texture, position,scaleFactor) {}

void Ghost::move(GameObject &other) {

}
