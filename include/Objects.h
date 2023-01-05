#pragma once
#include <SFML/Graphics.hpp>


class Objects{
public:
    // C-tor
    Objects(int maxV);
    // Public Funcs

    char getType() const;
    sf::Texture* getText() const;
    void draw(sf::RenderWindow *window) const;
    void setTexture(sf::Texture *texture);

private:
    // private members
    sf::Vector2f m_position;
    sf::Texture* m_texture;
    sf::Sprite m_sprite;
};