#include "Ghost.h"

Ghost::Ghost(sf::Texture *texture, sf::Vector2f position, float scaleFactor)
    : DynamicObject(texture, position,scaleFactor) {}

void Ghost::move(float deltaTime, Bounds boardBounds){
    std::vector<sf::Vector2f> dirs = {sf::Vector2f(0,1),sf::Vector2f(0,-1),sf::Vector2f(1,0),sf::Vector2f(-1,0)};
    moveObj(dirs[rand()%4], deltaTime);
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
    cancelMove();
}

void Ghost::handleCollision(Wall & wall) {
    cancelMove();
}
