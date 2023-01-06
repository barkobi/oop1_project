#include "objects/DynamicObjects/DynamicObject.h"

Direction_t DynamicObject::getDirection() {return m_direction;}

DynamicObject::DynamicObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : GameObject(texture,position,scaleFactor),m_statPosition(position){}

sf::Vector2f DynamicObject::getPosition() {return GameObject::getSprite().getPosition();}

void DynamicObject::goToInitialPosition() { GameObject::getSprite().setPosition(m_statPosition);}

void DynamicObject::setPosition(sf::Vector2f position) {
    m_sprite.setPosition(position);
}