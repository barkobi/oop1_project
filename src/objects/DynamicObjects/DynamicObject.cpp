#include "objects/DynamicObjects/DynamicObject.h"

DynamicObject::DynamicObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : GameObject(texture,position,scaleFactor),m_statPosition(position),m_previousPosition(position){}

sf::Vector2f DynamicObject::getPosition() {return GameObject::getSprite().getPosition();}

void DynamicObject::goToInitialPosition() { GameObject::getSprite().setPosition(m_statPosition);}

void DynamicObject::handleCollision(Wall& wall){
    m_sprite.setPosition(m_previousPosition);
}

void DynamicObject::moveObj(sf::Vector2f offset, float dt) {
    m_previousPosition = m_sprite.getPosition();
    m_sprite.move(offset * dt * BASE_SPEED);
}

void DynamicObject::cancelMove() {
    m_sprite.setPosition(m_previousPosition);
}

void DynamicObject::setPosition(sf::Vector2f position) {
    m_sprite.setPosition(position);
}

sf::Rect<float> DynamicObject::getGlobalBounds() {
    return m_sprite.getGlobalBounds();
}
