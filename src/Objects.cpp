#include "Objects.h"

#include "Objects.h"
#include "../resources/Consts.h"

// C-tor
Objects::Objects(int maxV) :  m_position(-1, -1), m_texture(NULL){
    float scaleBy = ((WINDOW_WIDTH - MENU_WIDTH )/ maxV) / 1.8;
    scaleBy /= 512; // scale by the size of photos.
    m_sprite.setTexture(*m_texture);
    m_sprite.setPosition(m_position);
    m_sprite.setScale(scaleBy,scaleBy);
}

// set texture of an object.
void Objects::setTexture(sf::Texture *texture) { m_texture = texture;}

// get texture of an object
sf::Texture *Objects::getText() const {
    return m_texture;
}

// draw objects using create sprite.
void Objects::draw(sf::RenderWindow *window) const {
    window->draw(m_sprite);
}
