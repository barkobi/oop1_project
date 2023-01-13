//
// Created by Bar Kobi on 06/01/2023.
//

#include "objects/StaticObjects/Gift/Gift.h"

Gift::Gift(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : StaticObject(texture, position,scaleFactor) {}

void Gift::setHitten() {
    hitten = true;

}

bool Gift::isHitten() {
    return hitten;
}