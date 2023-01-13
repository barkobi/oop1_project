#include "Ghost.h"

Ghost::Ghost(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : DynamicObject(texture, position,scaleFactor) ,m_rect(0){}

void Ghost::move(float deltaTime, Bounds boardBounds){
    std::vector<sf::Vector2f> dirs = {sf::Vector2f(0,1),sf::Vector2f(0,-1),sf::Vector2f(1,0),sf::Vector2f(-1,0)};
    int i = rand()%4;
    moveObj(dirs[i], deltaTime);
    if(i == 0)
        m_rect = 3072;
    else if(i == 1)
        m_rect = 2048;
    else if(i == 2)
        m_rect = 0;
    else
        m_rect = 1024;

    m_rect+= 512;

}

void Ghost::handleCollision(GameObject &object) {
    if (&object == this)
        return;

    object.handleCollision(*this);
}

void Ghost::handleCollision(Ghost & ghost) {
//    cancelMove();
}

void Ghost::handleCollision(Key & key) {
    cancelMove();
}

void Ghost::handleCollision(Door & door) {
    std::cout << "GHOST HIT DOOR\n";
    cancelMove();
}

void Ghost::handleCollision(Cookie & cookie) {
    cancelMove();
}

void Ghost::handleCollision(Pacman & pacman) {
    printf("ghost collision with pacman\n");
    cancelMove();
}

void Ghost::handleCollision(Gift & gift) {
    std::cout << "ABSTARCT CLASS GIFT";
    cancelMove();
}

void Ghost::handleCollision(Wall & wall) {
    cancelMove();
}

void Ghost::updateAnimation() {
    setIntRectGhost(m_rect);
}

void Ghost::handleCollision(TimeAddGift &) {

}
void Ghost::handleCollision(SuperPacGift &) {

}
void Ghost::handleCollision(LifeIncGift &) {

}
void Ghost::handleCollision(GhostFreezeGift &) {

}