#pragma once
#include "objects/GameObject.h"
#include "GameBoard.h"

enum Direction_t {UP , DOWN , LEFT , RIGHT};

class DynamicObject : public GameObject{
public:
    DynamicObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
    virtual ~DynamicObject() = default;

    void goToInitialPosition();

    virtual void move(float deltaTime, Bounds boardBounds) = 0;

    void handleCollision(Wall& wall);
    virtual void handleCollision(GameObject&) = 0;
    virtual void handleCollision(Pacman&) = 0;
    virtual void handleCollision(Ghost&) = 0;
    virtual void handleCollision(Key&) = 0;
    virtual void handleCollision(Door&) = 0;
    virtual void handleCollision(Cookie&) = 0;
    virtual void handleCollision(Gift&) = 0;
    void updateAnimation();
protected:
    void rotateObject(float rotateBy);
    sf::Vector2f getPosition();
    sf::Rect<float> getGlobalBounds();
    void moveObj(sf::Vector2f offset, float dt);
    void cancelMove();
    void setPosition(sf::Vector2f position);
private:
    int m_rect = 0;
    sf::Vector2f m_statPosition;
    float m_speedPerSecond = SPEED;
    sf::Vector2f m_previousPosition;
};

