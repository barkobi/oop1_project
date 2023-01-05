#include "GameObject.h"

GameObject::GameObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor) {
    m_sprite.setTexture(*texture);
    m_sprite.setPosition(position);

    m_sprite.setScale(scaleFactor,scaleFactor);
}

sf::Sprite &GameObject::getSprite() {return m_sprite;}

void GameObject::draw(sf::RenderWindow *window) const {
    window->draw(m_sprite);
}