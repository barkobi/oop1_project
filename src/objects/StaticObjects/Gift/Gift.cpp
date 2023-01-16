
#include "Gift.h"

Gift::Gift(sf::Texture *texture, sf::Vector2f position, float scaleFactor,float tileSize)
    : StaticObject(texture, position,scaleFactor,tileSize) {}

void Gift::openGift(){
    if(is_open)
        return;
    ResourcesManager::instance().playSound(GOT_GIFT);
    is_open = true;
}

bool Gift::isOpen(){
    return is_open;
}

void Gift::animation() {
    if(is_open){
        if(m_count == 9)
            deleteObject();

        m_rect += IMAGE_DIMENSIONS;
        m_count++;
        m_sprite.setTextureRect(sf::IntRect(m_rect,0,512,512));
    }
}