#include "Ghost.h"

Ghost::Ghost(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : DynamicObject(texture, position,scaleFactor) {}

void Ghost::move(float deltaTime) {
    m_previousPosition = m_sprite.getPosition();
    m_sprite.move(m_direction * m_speedPerSecond * deltaTime);
}

void Ghost::handleCollision(GameObject &object) {
    if (&object == this)
        return;

    object.handleCollision(*this);
}

void Ghost::handleCollision(Ghost & ghost) {
    m_sprite.setPosition(m_previousPosition);
}

void Ghost::handleCollision(Key & key) {
    m_sprite.setPosition(m_previousPosition);
}

void Ghost::handleCollision(Door & door) {
    m_sprite.setPosition(m_previousPosition);
}

void Ghost::handleCollision(Cookie & cookie) {
    m_sprite.setPosition(m_previousPosition);
}

void Ghost::handleCollision(Pacman & pacman) {
    m_sprite.setPosition(m_previousPosition);
}

void Ghost::handleCollision(Gift & gift) {
    m_sprite.setPosition(m_previousPosition);
}

void Ghost::handleCollision(Wall & wall) {
    m_sprite.setPosition(m_previousPosition);
}
