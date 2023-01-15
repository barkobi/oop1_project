#include "TimeAddGift.h"

TimeAddGift::TimeAddGift(sf::Vector2f position, float scaleFactor)
    : Gift(ResourcesManager::instance().getObjectTexture(ADD_TIME_GIFT),position,scaleFactor) {}
