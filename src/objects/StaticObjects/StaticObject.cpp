#include "objects/StaticObjects/StaticObject.h"

StaticObject::StaticObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor,float tileSize)
    : GameObject(texture,position,scaleFactor,tileSize){}

bool StaticObject::needToDelete() const {
    return m_delete;
}

void StaticObject::deleteObject() {
    m_delete = true;
}