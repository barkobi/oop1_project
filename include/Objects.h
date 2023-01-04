#pragma once
#include <SFML/Graphics.hpp>


class Objects{
public:
    // C-tor
    Objects();
    // Public Funcs
    void setPosition(sf::Vector2f position,char type);
    char getType() const ;
    sf::Texture* getText() const;
    void draw(sf::RenderWindow *window,const int maxV) const;
    void setTexture(sf::Texture *texture);
    sf::Sprite create(const int maxV) const;

private:
    // private members
    sf::Vector2f m_position;
    sf::Texture* m_texture;
    char m_type;
};