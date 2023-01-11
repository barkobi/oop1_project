#include "Pacman.h"
#include "Cookie.h"
#include "Key.h"

Pacman::Pacman(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : DynamicObject(texture, position,scaleFactor),m_rect(0){}

void Pacman::move(float deltaTime, Bounds boardBounds){
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
        rotateObject(-180);
        offset =sf::Vector2f(-1, 0);
    }
    moveObj(offset, deltaTime);
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
    Event event(CollapseWithGhost);
    EventLoop::instance().addEvent(event);
    cancelMove();
}

void Pacman::handleCollision(Key & key) {
    Event event(GotKey ,7);
    EventLoop::instance().addEvent(event);
    key.deleteObject();
}

void Pacman::handleCollision(Door & door) {
    cancelMove();
}

void Pacman::handleCollision(Cookie & cookie) {
    if(!cookie.getHitten())
    {
        cookie.setAnim();
        cookie.setHitten();
        Event event(EatCookie ,5);
        EventLoop::instance().addEvent(event);
    }

}

void Pacman::handleCollision(Pacman & pacman) {
    printf("pacman\n");
    cancelMove();
}

void Pacman::handleCollision(Gift & gift) {
    printf("gift\n");
    cancelMove();
}

void Pacman::handleCollision(Wall & wall) {
    cancelMove();
}

void Pacman::updateAnimation() {
    if(m_rect > 2047)
        m_rect = 0;
    setIntRectPacman(m_rect);
    m_rect += 512;
}