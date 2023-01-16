#include "Pacman.h"
#include "Cookie.h"
#include "Key.h"
#include "LifeIncGift.h"
#include "GhostFreezeGift.h"
#include "TimeAddGift.h"
#include "SuperPacGift.h"
#include "Door.h"
#include "limits"
Pacman::Pacman(sf::Vector2f position, float scaleFactor)
    : DynamicObject(ResourcesManager::instance().getObjectTexture(PACMAN), position,scaleFactor),
      m_rect(0),pacstate(std::make_unique<NormalPacman>()){}

void Pacman::move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes){

    if(superClock.getElapsedTime().asSeconds() > 5 && m_issuper){
        downgradeToNormal();
    }

    sf::Vector2f offset;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        rotateObject(-90);
        offset =sf::Vector2f(0, -1);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        rotateObject(90);
        offset =sf::Vector2f(0, 1);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        rotateObject(0);
        offset =sf::Vector2f(1, 0);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        rotateObject(180);
        offset =sf::Vector2f(-1, 0);
    }

    moveObj(offset, deltaTime,boardBounds.speed);

    auto myPosition = getPosition();
    if(myPosition.x +getGlobalBounds().width >= boardBounds.BottomRightX)
        setPosition(sf::Vector2f(boardBounds.topLeftX,myPosition.y));
    if(myPosition.x < boardBounds.topLeftX)
        setPosition(sf::Vector2f(boardBounds.BottomRightX- getGlobalBounds().width,myPosition.y));
    if(myPosition.y + getGlobalBounds().height >= boardBounds.BottomRightY)
        setPosition(sf::Vector2f(myPosition.x,boardBounds.topLeftY));
    if(myPosition.y < boardBounds.topLeftY)
        setPosition(sf::Vector2f(myPosition.x,boardBounds.BottomRightY - getGlobalBounds().height));
}

void Pacman::handleCollision(GameObject &object) {
    if (&object == this)
        return;

    object.handleCollision(*this);
}

void Pacman::handleCollision(Ghost & ghost) {
    pacstate->handleWallCollision(ghost,*this);
}

void Pacman::handleCollision(Key & key) {
    Event event(GotKey ,7);
    EventLoop::instance().addEvent(event);
    key.deleteObject();
}

void Pacman::handleCollision(Door & door) {
    pacstate->handleWallCollision(door,*this);
}

void Pacman::handleCollision(Cookie & cookie) {
    if(!cookie.getHitten()){
        cookie.setHitten();
        Event event(EatCookie ,2);
        EventLoop::instance().addEvent(event);
    }

}

void Pacman::handleCollision(Pacman & pacman) {
    cancelMove();
}

void Pacman::handleCollision(Wall & wall) {
    cancelMove();
}

void Pacman::updateAnimation() {
    if(m_rect == IMAGE_DIMENSIONS*4)
        m_rect = 0;
    setIntRectPacman(m_rect);
    m_rect += IMAGE_DIMENSIONS;
}

void Pacman::handleCollision(GhostFreezeGift & gift) {
    if(!gift.isOpen()){
        gift.openGift();
        Event event(GotGhostFreezeGift ,5);
        EventLoop::instance().addEvent(event);
    }
}

void Pacman::handleCollision(LifeIncGift & gift) {
    if(!gift.isOpen()){
        gift.openGift();
        Event event(GotLifeGift ,5);
        EventLoop::instance().addEvent(event);
    }
}

void Pacman::handleCollision(SuperPacGift &gift) {
    if(!gift.isOpen()){
        gift.openGift();
        Event event(GotSuperGift ,5);
        EventLoop::instance().addEvent(event);
    }
    upgradeToSuper();
    superClock.restart().asSeconds();
}


void Pacman::handleCollision(TimeAddGift & gift) {
    if(!gift.isOpen())
    {
        gift.openGift();
        Event event(GotTimeAddGift ,5);
        EventLoop::instance().addEvent(event);
    }
}

void Pacman::handleCollision(Gift &) {}

void Pacman::upgradeToSuper() {
    m_issuper = true;
    pacstate.reset(new SuperPacmanState());
}

void Pacman::downgradeToNormal() {
    m_issuper = false;
    pacstate.reset(new NormalPacman());
}
