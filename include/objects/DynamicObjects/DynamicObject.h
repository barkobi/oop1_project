#pragma once
#include "objects/GameObject.h"

enum Direction_t {UP , DOWN , LEFT , RIGHT};
class DynamicObject : public GameObject{
public:
    DynamicObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
    virtual void move(GameObject &other) = 0;
    Direction_t getDirection();
//    sf::Vector2f getPosition();
    void goToInitialPosition();
private:
    Direction_t m_direction;
    sf::Vector2f m_statPosition;
};

