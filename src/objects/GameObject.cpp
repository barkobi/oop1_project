#include "objects/GameObject.h"

GameObject::GameObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor) {
    m_sprite.setTexture(*texture);
    m_sprite.setPosition(position);
    m_sprite.setScale(scaleFactor/IMAGE_DIMENSIONS,scaleFactor/IMAGE_DIMENSIONS);
}

sf::Sprite &GameObject::getSprite() {return m_sprite;}

void GameObject::draw(sf::RenderWindow *window) {
    window->draw(m_sprite);
}

bool GameObject::checkCollision(GameObject &obj) {
    if (&obj == this)
        return false;
    return m_sprite.getGlobalBounds().intersects(obj.m_sprite.getGlobalBounds());
}
