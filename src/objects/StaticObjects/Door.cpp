#include <cmath>
#include "objects/StaticObjects/Door.h"

Door::Door(sf::Vector2f position, float scaleFactor,float tileSize)
    : StaticObject(ResourcesManager::instance().getObjectTexture(DOOR), position, scaleFactor,tileSize){}

/**
 * calculate distance from given position
 * @param pos the position to calculate distance from
 * @return the calculated distance
 */
float Door::checkDistance(const sf::Vector2f &pos) {
    auto dorpos = getSprite().getPosition();
    return sqrt(pow(pos.x - dorpos.x, 2) + pow(pos.y - dorpos.y, 2));
}

/**
 * if the door is opened, update the animation,
 * give a sense like open door.
 */
void Door::animation() {
    if(m_isOpen){
        if(m_count == 4)
            deleteObject();

        m_rect += IMAGE_DIMENSIONS;
        m_count++;
        m_sprite.setTextureRect(sf::IntRect(m_rect,0,512,512));
    }
}

/**
 * open a door, play open door sound
 */
void Door::openDoor() {
    if(m_isOpen)
        return;
    ResourcesManager::instance().playSound(OPEN_DOOR);
    m_isOpen = true;
}

bool Door::isOpen() {return m_isOpen;}