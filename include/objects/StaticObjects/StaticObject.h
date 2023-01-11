#pragma once
#include "objects/GameObject.h"
#include "iostream"

class StaticObject : public GameObject{
public:
    StaticObject(sf::Texture *texture, sf::Vector2f position, float scaleFactor);
    virtual ~StaticObject() = default;


    virtual void handleCollision(GameObject&) = 0;
    virtual void handleCollision(Pacman&) = 0;
    virtual void handleCollision(Ghost&) = 0;
    virtual void handleCollision(Wall&){};
    virtual void handleCollision(Key&){};
    virtual void handleCollision(Door&){};
    virtual void handleCollision(Cookie&) {};
    virtual void handleCollision(Gift&) {};
    virtual float checkDistance(const sf::Vector2f&) = 0;
    bool needToDelete() const;
    virtual void animation() = 0;
    void deleteObject();
protected:
private:
    bool m_delete = false;
};
