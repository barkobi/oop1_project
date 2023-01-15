#include "SuperPacGift.h"

SuperPacGift::SuperPacGift(sf::Vector2f position, float scaleFactor)
        : Gift(ResourcesManager::instance().getObjectTexture(SUPER_PM_GIFT), position,scaleFactor) {}