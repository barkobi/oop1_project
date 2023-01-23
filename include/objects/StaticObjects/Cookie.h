#pragma once

#include "StaticObject.h"
#include "objects/DynamicObjects/ghosts/Ghost.h"
#include "Pacman.h"

/**
 * Cookie class heiress from static objects
 */
class Cookie : public StaticObject{
public:
    // C-Tor
    Cookie(sf::Vector2f position, float scaleFactor,float tileSize);

    // Functions
    void handleCollision(GameObject& object) { object.handleCollision(*this); }
    void handleCollision(Pacman& player) { player.handleCollision(*this); }
    void handleCollision(Ghost& gameObject) { gameObject.handleCollision(*this); }
    virtual void animation();
    virtual float checkDistance(const sf::Vector2f& pos){return WINDOW_WIDTH;}
    void setHitten();
    bool getHitten();
private:
    // members
    int m_height = 0;
    int m_rect = 0;
    int m_count = 0;
    bool isHitten = false;

};
