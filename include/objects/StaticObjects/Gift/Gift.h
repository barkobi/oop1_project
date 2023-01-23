#pragma once

#include "StaticObject.h"
#include "objects/DynamicObjects/ghosts/Ghost.h"
#include "Pacman.h"

/**
 * Gift class heiress from static objects
 */
class Gift : public StaticObject{
public:
    // C-Tor
    Gift(sf::Texture *texture, sf::Vector2f position, float scaleFactor,float tileSize);

    // virtual functions for handling in the classes that heiress from gift
    void handleCollision(GameObject& object) = 0;
    void handleCollision(Pacman& player) = 0;
    void handleCollision(Ghost& gameObject) = 0;
    virtual void animation();
    virtual float checkDistance(const sf::Vector2f& pos){return WINDOW_WIDTH;}
    // public functions
    void openGift();
    bool isOpen();
private:
    // members
    int m_rect = 0;
    int m_count = 0;
    bool is_open = false;
};