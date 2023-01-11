
#include "Cookie.h"

Cookie::Cookie(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : StaticObject(texture, position,scaleFactor) {}

void Cookie::animation() {
    if(update){
        if(m_count == 9)
            deleteObject();
        m_rect += 512;
        m_height -= 1;
        m_count++;
        m_sprite.setTextureRect(sf::IntRect(m_rect,0,512,512));
        m_sprite.setPosition(m_sprite.getPosition().x,m_sprite.getPosition().y + m_height);
    }
}

void Cookie::setAnim() {
    update = true;
}

void Cookie::setHitten() {
    isHitten = true;

}

bool Cookie::getHitten() {
    return isHitten;
}
