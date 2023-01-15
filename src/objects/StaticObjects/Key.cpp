
#include "Key.h"

Key::Key(sf::Vector2f position, float scaleFactor)
    : StaticObject(ResourcesManager::instance().getObjectTexture(KEY), position,scaleFactor) {}
