#include "objects/DynamicObjects/DynamicObject.h"

DynamicObject::DynamicObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : GameObject(texture,position,scaleFactor),m_statPosition(position),m_previousPosition(position){}

//sf::Vector2f DynamicObject::getPosition() {return GameObject::getSprite().getPosition();}

void DynamicObject::goToInitialPosition() { GameObject::getSprite().setPosition(m_statPosition);}

void DynamicObject::setDirection(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::Key::Left:
            m_direction = sf::Vector2f(-1, 0);
            break;

        case sf::Keyboard::Key::Right:
            m_direction = sf::Vector2f(1, 0);
            break;

        case sf::Keyboard::Key::Up:
            m_direction = sf::Vector2f(0, -1);
            break;

        case sf::Keyboard::Key::Down:
            m_direction = sf::Vector2f(0, 1);
            break;

        default:
            m_direction = sf::Vector2f(0, 0);
            break;
    }
}

void DynamicObject::handleCollision(Wall& wall)
{
    m_sprite.setPosition(m_previousPosition);
}