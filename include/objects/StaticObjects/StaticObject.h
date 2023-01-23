#pragma once
#include "objects/GameObject.h"
#include "iostream"

/**
 * Static Objects class that heiress from GameObjects class
 */
class StaticObject : public GameObject{
public:
    // C-Tor and D-Tor
    StaticObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor,float tileSize);
    virtual ~StaticObject() = default;

    // virtual functions from handling collisions
    virtual void handleCollision(GameObject&) = 0;
    virtual void handleCollision(Pacman&) = 0;
    virtual void handleCollision(Ghost&) = 0;
    virtual void handleCollision(Wall&){};
    virtual void handleCollision(Key&){};
    virtual void handleCollision(Door&){};
    virtual void handleCollision(Cookie&) {};
    virtual void handleCollision(Gift&) {};
    virtual float checkDistance(const sf::Vector2f&) = 0;
    virtual void animation() = 0;
    // functions
    bool needToDelete() const;
    void deleteObject();
protected:
private:
    // member
    bool m_delete = false;
};
