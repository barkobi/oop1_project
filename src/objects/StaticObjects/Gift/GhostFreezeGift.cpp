#include "GhostFreezeGift.h"

GhostFreezeGift::GhostFreezeGift(sf::Vector2f position, float scaleFactor,float tileSize)
        : Gift(ResourcesManager::instance().getObjectTexture(GHOST_FREEZE_GIFT),position,scaleFactor,tileSize) {}