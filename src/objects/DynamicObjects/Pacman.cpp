
#include "Pacman.h"

Pacman::Pacman(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : DynamicObject(texture, position,scaleFactor) {}

void Pacman::move() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        setPosition(getPosition() + sf::Vector2f(0, -1));
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        setPosition(getPosition() + sf::Vector2f(0, 1));
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        setPosition(getPosition() + sf::Vector2f(1, 0));
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        setPosition(getPosition() + sf::Vector2f(-1, 0));
    }
}
