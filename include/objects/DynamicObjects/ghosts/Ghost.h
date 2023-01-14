#pragma once
#include "DynamicObject.h"

enum Direction_t{Right, Left, Up, Down};

class Ghost : public DynamicObject{
public:
    Ghost(sf::Texture *texture, sf::Vector2f position, float scaleFactor);

    virtual void handleCollision(GameObject&);
    virtual void handleCollision(Pacman&);
    virtual void handleCollision(Ghost&);
    virtual void handleCollision(Key&);
    virtual void handleCollision(Door&);
    virtual void handleCollision(Cookie&);
    virtual void handleCollision(TimeAddGift&);
    virtual void handleCollision(GhostFreezeGift&);
    virtual void handleCollision(LifeIncGift&);
    virtual void handleCollision(SuperPacGift&);
    virtual void handleCollision(Gift&);
    virtual void handleCollision(Wall&);
    virtual void updateAnimation();

protected:
    void moveGhost(float deltaTime, Direction_t);
    bool badMove = false;

private:
    int m_rect;
    bool frame;

};
