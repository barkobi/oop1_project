#include "Object.h"

#include "../resources/Consts.h"

// C-tor
Object::Object() :  m_position(-1, -1), m_texture(NULL){}

Object::Object(sf::Texture *texture , sf::Vector2f position) : m_texture(texture), m_position(position) {
    float scaleBy = ((WINDOW_WIDTH - MENU_WIDTH )/ 10) / 1.8;
    scaleBy /= 512; // scale by the size of photos.
    m_sprite.setTexture(*m_texture);
    m_sprite.setPosition(m_position);
    m_sprite.setScale(scaleBy,scaleBy);
}

// get texture of an object
sf::Texture *Object::getTexture() const {
    return m_texture;
}

// draw objects using create sprite.
void Object::draw(sf::RenderWindow *window) const {
    window->draw(m_sprite);
}
