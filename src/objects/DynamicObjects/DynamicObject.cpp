#include "objects/DynamicObjects/DynamicObject.h"

DynamicObject::DynamicObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : GameObject(texture,position,scaleFactor),m_statPosition(position),m_previousPosition(position){
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
    static auto originalScale = m_sprite.getScale();
    m_sprite.setScale(originalScale);

    if(m_sprite.getRotation() == rotateBy)
        return;

    m_sprite.rotate(-m_sprite.getRotation());
    if(rotateBy == 180)
        m_sprite.setScale(-originalScale.x, originalScale.y);
    else
        m_sprite.rotate(rotateBy);
}

void DynamicObject::setIntRectPacman(int rect) {
    m_sprite.setTextureRect(sf::IntRect(0,rect,512,512));
}


void DynamicObject::setIntRectGhost(int rect) {
    m_sprite.setTextureRect(sf::IntRect(rect,0,512,512));
}
