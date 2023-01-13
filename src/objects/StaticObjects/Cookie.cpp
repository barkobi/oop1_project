#include "cmath"
#include "Cookie.h"

Cookie::Cookie(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : StaticObject(texture, position,scaleFactor) {}

void Cookie::animation() {
    if(isHitten){
        if(m_count == 9)
            deleteObject();
        else if(m_count > 5)
           m_height =  std::abs(m_height += 4);
        else if(m_count < 5)
            m_height -= 4;

        std::cout << m_sprite.getPosition().y << "  \n";
        std::cout << m_height << " \n";
        m_rect += 512;
        m_count++;
        m_sprite.setTextureRect(sf::IntRect(m_rect,0,512,512));
        m_sprite.setPosition(m_sprite.getPosition().x,m_sprite.getPosition().y + m_height);
    }
}

void Cookie::setHitten() {
    isHitten = true;

}

bool Cookie::getHitten() {
    return isHitten;
}
