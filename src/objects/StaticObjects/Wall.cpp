#include "Wall.h"

Wall::Wall(sf::Vector2f position, float scaleFactor)
    : StaticObject(ResourcesManager::instance().getObjectTexture(WALL),position,scaleFactor) {}
