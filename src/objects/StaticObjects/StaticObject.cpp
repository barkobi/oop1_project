#include "objects/StaticObjects/StaticObject.h"

StaticObject::StaticObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : GameObject(texture,position,scaleFactor){}

bool StaticObject::needToDelete() const {
    return m_delete;
}

void StaticObject::deleteObject() {
    m_delete = true;
}
