
#include "Gift.h"

Gift::Gift( sf::Vector2f position, float scaleFactor)
    : StaticObject(ResourcesManager::instance().getObjectTexture(GIFT), position,scaleFactor) {}

void Gift::openGift(){
    if(is_open)
        return;
    ResourcesManager::instance().playSound(OPEN_DOOR);
    is_open = true;
}

bool Gift::isOpen(){

    return is_open;
}

void Gift::animation() {
    if(is_open){
        if(m_count == 8)
            deleteObject();

        m_rect += IMAGE_DIMENSIONS;
        m_count++;
        m_sprite.setTextureRect(sf::IntRect(m_rect,0,512,512));
    }
}