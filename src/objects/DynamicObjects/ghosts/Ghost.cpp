#include "objects/DynamicObjects/ghosts/Ghost.h"
#include "Pacman.h"

Ghost::Ghost(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : DynamicObject(texture, position,scaleFactor) ,m_rect(0){}

void Ghost::moveGhost(float deltaTime, Bounds boardBounds, Direction_t direction){
    std::vector<sf::Vector2f> dirs = {sf::Vector2f(1,0),sf::Vector2f(-1,0),sf::Vector2f(0,-1),sf::Vector2f(0,1)};
    moveObj(dirs[direction], deltaTime);

    auto myPosition = getPosition();
    if((myPosition.x +getGlobalBounds().width >= boardBounds.BottomRightX)
    || (myPosition.x < boardBounds.topLeftX)
    || (myPosition.y + getGlobalBounds().height >= boardBounds.BottomRightY)
    || (myPosition.y < boardBounds.topLeftY))
        cancelMove();

    m_rect = (direction*IMAGE_DIMENSIONS)*2;
}

void Ghost::handleCollision(GameObject &object) {
    if (&object == this)
        return;

    object.handleCollision(*this);
}

void Ghost::handleCollision(Ghost & ghost) {}

void Ghost::handleCollision(Key & key) {}

void Ghost::handleCollision(Door & door) {
    cancelMove();
}

void Ghost::handleCollision(Cookie & cookie) {}

void Ghost::handleCollision(Pacman & pacman) {}

void Ghost::handleCollision(Gift & gift) {}

void Ghost::handleCollision(Wall & wall) {
    cancelMove();
}

void Ghost::updateAnimation(){
    frame = !frame;
    setIntRectGhost(m_rect + IMAGE_DIMENSIONS*frame);
}

void Ghost::handleCollision(TimeAddGift &) {}
void Ghost::handleCollision(SuperPacGift &) {}
void Ghost::handleCollision(LifeIncGift &) {}
void Ghost::handleCollision(GhostFreezeGift &) {}