#include "GhostFreezeGift.h"

GhostFreezeGift::GhostFreezeGift(sf::Vector2f position, float scaleFactor)
        : Gift(ResourcesManager::instance().getObjectTexture(GHOST_FREEZE_GIFT),position,scaleFactor) {}