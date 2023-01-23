#include "Pacman.h"

#include <memory>
#include "Cookie.h"
#include "Key.h"
#include "LifeIncGift.h"
#include "GhostFreezeGift.h"
#include "TimeAddGift.h"
#include "SuperPacGift.h"
#include "Door.h"

Pacman::Pacman(sf::Vector2f position, float scaleFactor,float tileSize)
    : DynamicObject(ResourcesManager::instance().getObjectTexture(PACMAN), position,scaleFactor,tileSize),
      m_rect(0),pacstate(std::make_unique<NormalPacman>()){
}

/**
 * move the pacman
 * @param deltaTime how much time passed till last movement
 * @param boardBounds board bounds
 * @param bfsRes result of BFS, *ignore*
 */
void Pacman::move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes){
    // check if need to downgrade to normal pacman.
    if(superClock.getElapsedTime().asSeconds() > 5 && m_issuper){
        downgradeToNormal();
    }

    // set the offset according to what key pressed.
    // and rotate the object.
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

    // move the object
    moveObj(offset, deltaTime,boardBounds.speed + 5);

    // if went off the board use teleport.
    // set the location to the other side of the board.
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

//-------------- handle collisions with all the objects ----------------
// collide with wall -> cancel move
// collide with door/ghost -> use handle collision of the state
// otherwise add the relevant event to the event loop.

void Pacman::handleCollision(GameObject &object) {
    if (&object == this)
        return;

    object.handleCollision(*this);
}

void Pacman::handleCollision(Ghost & ghost) {
    pacstate->handleWallCollision(ghost,*this);
}

void Pacman::handleCollision(Key & key) {
    Event event(GotKey ,KEY_P);
    EventLoop::instance().addEvent(event);
    key.deleteObject();
}

void Pacman::handleCollision(Door & door) {
    pacstate->handleWallCollision(door,*this);
}

void Pacman::handleCollision(Cookie & cookie) {
    if(!cookie.getHitten()){
        cookie.setHitten();
        Event event(EatCookie ,COOKIE_P);
        EventLoop::instance().addEvent(event);
    }

}

void Pacman::handleCollision(Pacman & pacman) {
    cancelMove();
}

void Pacman::handleCollision(Wall & wall) {
    cancelMove();
}

void Pacman::handleCollision(GhostFreezeGift & gift) {
    if(!gift.isOpen()){
        gift.openGift();
        Event event(GotGhostFreezeGift ,GIFT_P);
        EventLoop::instance().addEvent(event);
    }
}

void Pacman::handleCollision(LifeIncGift & gift) {
    if(!gift.isOpen()){
        gift.openGift();
        Event event(GotLifeGift ,GIFT_P);
        EventLoop::instance().addEvent(event);
    }
}

void Pacman::handleCollision(SuperPacGift &gift) {
    if(!gift.isOpen()){
        gift.openGift();
        Event event(GotSuperGift ,GIFT_P);
        EventLoop::instance().addEvent(event);
    }
    upgradeToSuper();
    superClock.restart().asSeconds();
}


void Pacman::handleCollision(TimeAddGift & gift) {
    if(!gift.isOpen())
    {
        gift.openGift();
        Event event(GotTimeAddGift ,GIFT_P);
        EventLoop::instance().addEvent(event);
    }
}

void Pacman::handleCollision(Gift &) {}

//-------------- end of handle collisions ----------------

/**
 * update the animation, give a sense eating mouth.
 */
void Pacman::updateAnimation() {
    if(m_rect == IMAGE_DIMENSIONS*4)
        m_rect = 0;
    setIntRect(sf::IntRect(0,m_rect,m_sprite.getTextureRect().width,m_sprite.getTextureRect().height));
    m_rect += IMAGE_DIMENSIONS;
}

/**
 * upgrade the pacman to super pacman
 */
void Pacman::upgradeToSuper() {
    m_issuper = true;
    pacstate = std::make_unique<SuperPacmanState>();
}

/**
 * downgrade the pacman to normal pacman
 */
void Pacman::downgradeToNormal() {
    m_issuper = false;
    pacstate = std::make_unique<NormalPacman>();
}
