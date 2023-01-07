#pragma once
#include <SFML/Graphics.hpp>
#include "../../resources/Consts.h"

class Pacman;
class Wall;
class Key;
class Ghost;
class Door;
class Cookie;
class Gift;

class GameObject{
public:
    // C-tor
    GameObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
    virtual ~GameObject() = default;

    // Public Funcs
    void draw(sf::RenderWindow *window);
    sf::Sprite &getSprite() ;
    bool checkCollision(GameObject& obj);

    virtual void handleCollision(GameObject&) = 0;
    virtual void handleCollision(Pacman&) = 0;
    virtual void handleCollision(Ghost&) = 0;
    virtual void handleCollision(Wall&) = 0;
    virtual void handleCollision(Key&) = 0;
    virtual void handleCollision(Door&) = 0;
    virtual void handleCollision(Cookie&) = 0;
    virtual void handleCollision(Gift&) = 0;

protected:
    sf::Sprite m_sprite;

};