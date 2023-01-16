#pragma once

#include "StaticObject.h"
#include "objects/DynamicObjects/ghosts/Ghost.h"
#include "Pacman.h"

class Gift : public StaticObject{
public:
    Gift(sf::Texture *texture, sf::Vector2f position, float scaleFactor,float tileSize);

    void handleCollision(GameObject& object) = 0;
    void handleCollision(Pacman& player) = 0;
    void handleCollision(Ghost& gameObject) = 0;
    virtual void animation();
    virtual float checkDistance(const sf::Vector2f& pos){return WINDOW_WIDTH;}
    void openGift();
    bool isOpen();
private:
    int m_rect = 0;
    int m_count = 0;
    bool is_open = false;
};