
#include "Key.h"

Key::Key(sf::Vector2f position, float scaleFactor,float tileSize)
    : StaticObject(ResourcesManager::instance().getObjectTexture(KEY), position,scaleFactor,tileSize) {}
