#include "Pacman.h"

Pacman::Pacman(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : DynamicObject(texture, position,scaleFactor){}

void Pacman::move(float deltaTime) {
    m_previousPosition = m_sprite.getPosition();
    m_sprite.move(m_direction * deltaTime * BASE_SPEED);
}

void Pacman::handleCollision(GameObject &object) {
    if (&object == this)
        return;

    object.handleCollision(*this);
}

void Pacman::handleCollision(Ghost & ghost) {
    m_sprite.setPosition(m_previousPosition);
}

void Pacman::handleCollision(Key & key) {
    m_sprite.setPosition(m_previousPosition);
}

void Pacman::handleCollision(Door & door) {
    m_sprite.setPosition(m_previousPosition);
}

void Pacman::handleCollision(Cookie & cookie) {
    m_sprite.setPosition(m_previousPosition);
}

void Pacman::handleCollision(Pacman & pacman) {
    m_sprite.setPosition(m_previousPosition);
}

void Pacman::handleCollision(Gift & gift) {
    m_sprite.setPosition(m_previousPosition);
}

void Pacman::handleCollision(Wall & wall) {
    m_sprite.setPosition(m_previousPosition);
}

