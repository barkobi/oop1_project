#pragma once
#include "objects/GameObject.h"

enum Direction_t {UP , DOWN , LEFT , RIGHT};

class DynamicObject : public GameObject{
public:
    DynamicObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
    virtual void move() = 0;
    Direction_t getDirection();
    void goToInitialPosition();

protected:
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f position);

private:
    Direction_t m_direction;
    sf::Vector2f m_statPosition;
};

