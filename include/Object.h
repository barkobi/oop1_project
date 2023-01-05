#pragma once
#include <SFML/Graphics.hpp>


class Object{
public:
    // C-tor
    Object();
    Object(sf::Texture *texture, sf::Vector2f position);
    // Public Funcs

    sf::Texture* getTexture() const;
    void draw(sf::RenderWindow *window) const;

private:
    // private members
    sf::Vector2f m_position;
    sf::Texture* m_texture;
    sf::Sprite m_sprite;
};