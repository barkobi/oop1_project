#include "objects/DynamicObjects/DynamicObject.h"

DynamicObject::DynamicObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : GameObject(texture,position,scaleFactor),m_statPosition(position),m_previousPosition(position),m_rect(0){
}
sf::Vector2f DynamicObject::getPosition() {return GameObject::getSprite().getPosition();}

void DynamicObject::goToInitialPosition() { GameObject::getSprite().setPosition(m_statPosition);}

void DynamicObject::handleCollision(Wall& wall){
    m_sprite.setPosition(m_previousPosition);
}

void DynamicObject::moveObj(sf::Vector2f offset, float dt) {
    m_previousPosition = m_sprite.getPosition();
    m_sprite.move(offset * dt * SPEED);
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

void DynamicObject::rotateObject(float rotateBy) {
    if(m_sprite.getRotation() == rotateBy)
        return;

    m_sprite.rotate(-m_sprite.getRotation());
    m_sprite.rotate(rotateBy);
}

void DynamicObject::updateAnimation() {
    if(m_rect >= 1536)
        m_rect = 0;
    m_sprite.setTextureRect(sf::IntRect(0,m_rect,512,512));
    m_rect += 512;
}
