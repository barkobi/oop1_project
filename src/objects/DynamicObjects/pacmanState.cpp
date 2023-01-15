#include "pacmanState.h"
#include "Pacman.h"
#include "Door.h"
#include "Ghost.h"

void SuperPacmanState::handleWallCollision(Door &door, Pacman &pacman) {
    if(!door.isOpen())
        door.openDoor();
}

void SuperPacmanState::handleWallCollision(Ghost &ghost, Pacman &pacman) {
    ghost.goToInitialPosition();
}

void NormalPacman::handleWallCollision(Door &door, Pacman &pacman) {
    if(!door.isOpen())
        pacman.cancelMove();
}

void NormalPacman::handleWallCollision(Ghost &ghost, Pacman &pacman) {
    EventLoop::instance().addEvent(Event(CollapseWithGhost));
}