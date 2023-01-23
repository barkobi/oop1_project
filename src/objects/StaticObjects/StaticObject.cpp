#include "objects/StaticObjects/StaticObject.h"

StaticObject::StaticObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor,float tileSize)
    : GameObject(texture,position,scaleFactor,tileSize){}

/**
 * is the object need to be deleted
 */
bool StaticObject::needToDelete() const {
    return m_delete;
}

/**
 * mark object as need to be deleted.
 * ** will be deleted by the controller **
 */
void StaticObject::deleteObject() {
    m_delete = true;
}