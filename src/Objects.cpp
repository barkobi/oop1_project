#include "Objects.h"

#include "Objects.h"
#include "../resources/Consts.h"

// C-tor
Objects::Objects() :  m_position(-1, -1), m_texture(NULL){}

// set position of an object with he's type
void Objects::setPosition(sf::Vector2f position,char type) {
    m_position = position;
    m_type = type;
}

// set texture of an object.
void Objects::setTexture(sf::Texture *texture) { m_texture = texture;}

// get texture of an object
sf::Texture *Objects::getText() const {
    return m_texture;
}

// draw objects using create sprite.
void Objects::draw(sf::RenderWindow *window,const int maxV) const {
    window->draw(create(maxV));
}

// create sprite from texture.
sf::Sprite Objects::create(const int maxV) const{

    float scaleBy = ((WINDOW_WIDTH - MENU_WIDTH )/ maxV) / 1.8;
    scaleBy /= 512; // scale by the size of photos.
    auto result = sf::Sprite(*m_texture);
    result.setPosition(m_position);
    result.setScale(scaleBy,scaleBy);

    return result; // return sprite.
}

// return type of an object.
char Objects::getType() const { return m_type;}
