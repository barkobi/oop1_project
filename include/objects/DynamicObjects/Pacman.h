#pragma once
#include "pacmanState.h"
#include "DynamicObject.h"
#include "eventLoop.h"
#include "../../../values/Points.h"

/**
 * Pacman class heiress from Dynamic object class
 */
class Pacman : public DynamicObject{
public:
    // C-tor
    Pacman(sf::Vector2f position, float scaleFactor,float tileSize);

    // move function
    void move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes);

    // handle collision specific to each class
    virtual void handleCollision(GameObject&);
    virtual void handleCollision(Pacman&);
    virtual void handleCollision(Ghost& ghost);
    virtual void handleCollision(Key&);
    virtual void handleCollision(Door&);
    virtual void handleCollision(Cookie&);
    virtual void handleCollision(TimeAddGift&);
    virtual void handleCollision(GhostFreezeGift&);
    virtual void handleCollision(LifeIncGift&);
    virtual void handleCollision(SuperPacGift&);
    virtual void handleCollision(Gift&);
    virtual void handleCollision(Wall& wall);
    virtual void updateAnimation();

    // reset pacman state
    void upgradeToSuper();
    void downgradeToNormal();

private:
    // members
    sf::Clock superClock;
    int m_rect;
    // smart pointer to pacman current state.
    std::unique_ptr<PacmanState> pacstate;
    bool m_issuper = false;

};


