#pragma once
#include "DynamicObject.h"

// enum for the specific direction
enum Direction_t{Right, Left, Up, Down};

/**
 * ghost class heiress from dynamic object
 */
class Ghost : public DynamicObject{
public:
    Ghost(sf::Texture *texture, sf::Vector2f position, float scaleFactor,float tileSize);

    // functions for handling ghost collisions.
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
    // move ghost function that each subclass of ghost uses.
    void moveGhost(float deltaTime, Bounds boardBounds, Direction_t);

private:
    // members
    int m_rect;
    bool frame;
};
