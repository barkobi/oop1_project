#include "TimeAddGift.h"

TimeAddGift::TimeAddGift(sf::Vector2f position, float scaleFactor,float tileSize)
    : Gift(ResourcesManager::instance().getObjectTexture(ADD_TIME_GIFT),position,scaleFactor,tileSize) {}
