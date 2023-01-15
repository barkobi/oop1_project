#include "LifeIncGift.h"

LifeIncGift::LifeIncGift(sf::Vector2f position, float scaleFactor)
        : Gift(ResourcesManager::instance().getObjectTexture(ADD_LIFE_GIFT), position,scaleFactor) {}
