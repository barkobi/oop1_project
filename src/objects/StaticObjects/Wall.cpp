#include "Wall.h"

Wall::Wall(sf::Vector2f position, float scaleFactor,float tileSize)
    : StaticObject(ResourcesManager::instance().getObjectTexture(WALL),position,scaleFactor,tileSize) {}
