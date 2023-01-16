#include "objects/GameObject.h"
#include "iostream"
GameObject::GameObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor,float tileSize) {
    m_sprite.setTexture(*texture);
    m_sprite.setTextureRect(sf::IntRect (0,0,IMAGE_DIMENSIONS,IMAGE_DIMENSIONS));
    m_sprite.setPosition(position);
    m_sprite.setOrigin(m_sprite.getGlobalBounds().width * 0.5,m_sprite.getGlobalBounds().height * 0.5);
    m_sprite.setScale((tileSize/IMAGE_DIMENSIONS)*scaleFactor,(tileSize/IMAGE_DIMENSIONS)*scaleFactor);
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
