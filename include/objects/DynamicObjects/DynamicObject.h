#pragma once
#include "objects/GameObject.h"

enum Direction_t {UP , DOWN , LEFT , RIGHT};

class DynamicObject : public GameObject{
public:
    DynamicObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
    virtual ~DynamicObject() = default;

    void setDirection(sf::Keyboard::Key key);
    void goToInitialPosition();

    virtual void move(float deltaTime) = 0;
    void handleCollision(Wall& wall);
    virtual void handleCollision(GameObject&) = 0;
    virtual void handleCollision(Pacman&) = 0;
    virtual void handleCollision(Ghost&) = 0;
    virtual void handleCollision(Key&) = 0;
    virtual void handleCollision(Door&) = 0;
    virtual void handleCollision(Cookie&) = 0;
    virtual void handleCollision(Gift&) = 0;
protected:
    sf::Vector2f m_direction;
    sf::Vector2f m_previousPosition;
    sf::Vector2f m_statPosition;
    float m_speedPerSecond = BASE_SPEED;

private:
};

