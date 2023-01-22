#pragma once
#include "objects/GameObject.h"
#include "GameBoard.h"


/**
 * class of the objects that moves during the game
 * heiress from GameObject class
 */
class DynamicObject : public GameObject{
public:
    DynamicObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor,float tileSize);


    // virtual functions
    virtual void move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes) = 0;
    virtual void handleCollision(GameObject&) = 0;
    virtual void handleCollision(Pacman&) = 0;
    virtual void handleCollision(Ghost&) = 0;
    virtual void handleCollision(Key&) = 0;
    virtual void handleCollision(Door&) = 0;
    virtual void handleCollision(Cookie&) = 0;
    virtual void handleCollision(TimeAddGift&) = 0;
    virtual void handleCollision(GhostFreezeGift&) = 0;
    virtual void handleCollision(LifeIncGift&) = 0;
    virtual void handleCollision(SuperPacGift&) = 0;
    virtual void handleCollision(Gift&) = 0;
    virtual void updateAnimation() = 0;

    // public functions
    void setTextureRegular();
    void setTexture(sf::Texture *texture);
    void goToInitialPosition();
    void handleCollision(Wall& wall);
    void setIntRectPacman(int rect);
    void setIntRectGhost(int rect);
    void cancelMove();

protected:
    // protected functions.
    void rotateObject(float rotateBy);
    sf::Vector2f getPosition();
    sf::Rect<float> getGlobalBounds();
    void moveObj(sf::Vector2f offset, float dt,float ObjectSpeed);
    void setPosition(sf::Vector2f position);
    sf::Vector2f m_origianlScale;
private:
    // private members
    sf::Vector2f m_statPosition;
    sf::Vector2f m_previousPosition;
    sf::Texture *originalTexture;
};

