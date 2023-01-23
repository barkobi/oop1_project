#include "objects/DynamicObjects/ghosts/Ghost.h"
#include "Pacman.h"


Ghost::Ghost(sf::Texture *texture, sf::Vector2f position, float scaleFactor,float tileSize)
    : DynamicObject(texture, position,scaleFactor,tileSize) ,m_rect(0){}

/**
 * move the ghost
 * @param deltaTime how much time passed till last movement
 * @param boardBounds board bounds.
 * @param direction what direction to move to.
 */
void Ghost::moveGhost(float deltaTime, Bounds boardBounds, Direction_t direction){

    std::vector<sf::Vector2f> dirs = {sf::Vector2f(1,0),sf::Vector2f(-1,0),  // RIGHT, LEFT,
                                      sf::Vector2f(0,-1),sf::Vector2f(0,1)}; // UP, DOWN.
    moveObj(dirs[direction], deltaTime,boardBounds.speed);

    auto myPosition = getPosition();
    // check if after the movement the ghost stayed in the board bounces.
    if((myPosition.x +getGlobalBounds().width >= boardBounds.BottomRightX)
    || (myPosition.x < boardBounds.topLeftX)
    || (myPosition.y + getGlobalBounds().height >= boardBounds.BottomRightY)
    || (myPosition.y < boardBounds.topLeftY))
        cancelMove();

    // update the ghost texture, set the eyes look to the movement direction.
    m_rect = (direction*IMAGE_DIMENSIONS)*2;
}

//-------------- handle collisions with all the objects ----------------
// cancel move if collide with door or wall, otherwise do nothing
// **collide with pacman handled in pacman.

void Ghost::handleCollision(GameObject &object) {
    if (&object == this)
        return;

    object.handleCollision(*this);
}

void Ghost::handleCollision(Door & door) {
    cancelMove();
}

void Ghost::handleCollision(Wall & wall) {
    cancelMove();
}

void Ghost::handleCollision(Ghost & ghost) {}
void Ghost::handleCollision(Key & key) {}
void Ghost::handleCollision(Cookie & cookie) {}
void Ghost::handleCollision(Pacman & pacman) {}
void Ghost::handleCollision(Gift & gift) {}
void Ghost::handleCollision(TimeAddGift &) {}
void Ghost::handleCollision(SuperPacGift &) {}
void Ghost::handleCollision(LifeIncGift &) {}
void Ghost::handleCollision(GhostFreezeGift &) {}

//-------------- end of handle collisions ----------------

/**
 * update the animation, give a sense like moving legs.
 */
void Ghost::updateAnimation(){
    frame = !frame;
    setIntRect(sf::IntRect(m_rect + IMAGE_DIMENSIONS*frame,0,512,512));
}