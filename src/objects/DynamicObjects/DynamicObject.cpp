#include "objects/DynamicObjects/DynamicObject.h"

DynamicObject::DynamicObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor,float tileSize)
    : GameObject(texture,position,scaleFactor,tileSize),m_statPosition(position),m_previousPosition(position) , originalTexture(texture){
    m_origianlScale = m_sprite.getScale();
}

/**
 * get object position
 * @return position
 */
sf::Vector2f DynamicObject::getPosition() {return GameObject::getSprite().getPosition();}

/**
 * move the object to the initial position on the board.
 */
void DynamicObject::goToInitialPosition() { GameObject::getSprite().setPosition(m_statPosition);}

/**
 * handle collide with wall.
 * @param wall
 */
void DynamicObject::handleCollision(Wall& wall){
    m_sprite.setPosition(m_previousPosition);
}

/**
 * move the object by given offset
 * @param offset the offset to move to.
 * @param dt how much time passed till last movement
 * @param ObjectSpeed the speed of the object
 */
void DynamicObject::moveObj(sf::Vector2f offset, float dt,float ObjectSpeed) {
    m_previousPosition = m_sprite.getPosition();
    m_sprite.move(offset * dt * (ObjectSpeed*3));
}

/**
 * cancel object move and move back to last position.
 */
void DynamicObject::cancelMove() {
    m_sprite.setPosition(m_previousPosition);
}

/**
 * set object position
 * @param position position to set
 */
void DynamicObject::setPosition(sf::Vector2f position) {
    m_sprite.setPosition(position);
}

/**
 * get object global bounds
 * @return object global bounds
 */
sf::Rect<float> DynamicObject::getGlobalBounds() {
    return m_sprite.getGlobalBounds();
}

/**
 * rotate the object
 * @param rotateBy how much degrees to rotate
 */
void DynamicObject::rotateObject(float rotateBy) {
    // set the scale to original.
    m_sprite.setScale(m_origianlScale);

    if(m_sprite.getRotation() == rotateBy)
        return;

    // rotate back to rotate according to original.
    m_sprite.rotate(-m_sprite.getRotation());
    // if rotate 180 do mirror
    if(rotateBy == 180)
        m_sprite.setScale(-m_origianlScale.x, m_origianlScale.y);
    else
        m_sprite.rotate(rotateBy);
}

/**
 * update intRect for animation handling
 * @param rect the intRect to set
 */
void DynamicObject::setIntRect(sf::IntRect rect) {
    m_sprite.setTextureRect(rect);
}

/**
 * set to original texture
 */
void DynamicObject::setTextureRegular() {
    m_sprite.setTexture(*originalTexture);
}

/**
 * set object texture
 * @param texture
 */
void DynamicObject::setTexture(sf::Texture *texture) {
    m_sprite.setTexture(*texture);
}