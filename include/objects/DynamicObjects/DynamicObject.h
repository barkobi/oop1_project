#pragma once
#include "objects/GameObject.h"
#include "GameBoard.h"

class DynamicObject : public GameObject{
public:
    DynamicObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
//    virtual ~DynamicObject() = default;

    void goToInitialPosition();

    virtual void move(float deltaTime, Bounds boardBounds ,std::vector<std::vector<int>> bfsRes) = 0;

    void handleCollision(Wall& wall);
    virtual void handleCollision(GameObject&) = 0;
    virtual void handleCollision(Pacman&) = 0;
    virtual void handleCollision(Ghost&) = 0;
    virtual void handleCollision(Key&) = 0;
    virtual void handleCollision(Door&) = 0;
    virtual void handleCollision(Cookie&) = 0;
    virtual void handleCollision(Gift&) = 0;
    virtual void updateAnimation() = 0;
    void setIntRectPacman(int rect);
    void setIntRectGhost(int rect);
protected:
    void rotateObject(float rotateBy);
    sf::Vector2f getPosition();
    sf::Rect<float> getGlobalBounds();
    void moveObj(sf::Vector2f offset, float dt);
    void cancelMove();
    void setPosition(sf::Vector2f position);
private:
    sf::Vector2f m_statPosition;
    float m_speedPerSecond = SPEED;
    sf::Vector2f m_previousPosition;
};

