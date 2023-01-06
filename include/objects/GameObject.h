#pragma once
#include <SFML/Graphics.hpp>
#include "../../resources/Consts.h"


class GameObject{
public:
    // C-tor
    GameObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor);

    // Public Funcs
    void draw(sf::RenderWindow *window) const;
    sf::Sprite &getSprite() ;

protected:
    sf::Sprite m_sprite;

};