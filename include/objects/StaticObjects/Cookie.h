#pragma once

#include "StaticObject.h"
#include "Ghost.h"
#include "Pacman.h"

class Cookie : public StaticObject{
public:
    Cookie(sf::Texture *texture, sf::Vector2f position, float scaleFactor);

    void handleCollision(GameObject& object) { object.handleCollision(*this); }
    void handleCollision(Pacman& player) { player.handleCollision(*this); }
    void handleCollision(Ghost& gameObject) { gameObject.handleCollision(*this); }
    virtual int checkDistance(sf::Vector2f& pos){return WINDOW_WIDTH;}
    virtual void animation();
    void setAnim();
    void setHitten();
    bool getHitten();
private:
    int m_height = 0;
    int m_rect = 0;
    int m_count = 0;
    bool update = false;
    bool isHitten = false;

};
