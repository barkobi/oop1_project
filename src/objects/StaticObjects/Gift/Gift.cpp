//
// Created by Bar Kobi on 06/01/2023.
//

#include "objects/StaticObjects/Gift/Gift.h"

Gift::Gift( sf::Vector2f position, float scaleFactor)
    : StaticObject(ResourcesManager::instance().getObjectTexture(GIFT), position,scaleFactor) {}

void Gift::setHitten() {
    hitten = true;

}

bool Gift::isHitten() {
    return hitten;
}