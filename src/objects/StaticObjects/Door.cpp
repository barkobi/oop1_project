#include <cmath>
#include "objects/StaticObjects/Door.h"

Door::Door(sf::Vector2f position, float scaleFactor)
    : StaticObject(ResourcesManager::instance().getObjectTexture(DOOR), position, scaleFactor){}

float Door::checkDistance(const sf::Vector2f &pos) {
    auto dorpos = this->getSprite().getPosition();
    return sqrt(pow(pos.x - dorpos.x, 2) + pow(pos.y - dorpos.y, 2));
}

void Door::animation() {
    if(m_isOpen){
        if(m_count == 3)
            deleteObject();

        m_rect += IMAGE_DIMENSIONS;
        m_count++;
        m_sprite.setTextureRect(sf::IntRect(m_rect,0,512,512));
    }
}

void Door::openDoor() {
    if(m_isOpen)
        return;
    ResourcesManager::instance().playSound(OPEN_DOOR);
    m_isOpen = true;
}

bool Door::isOpen() {return m_isOpen;}