#pragma once
#include "eventLoop.h"
#include "iostream"
class Ghost;
class Door;
class Pacman;

class PacmanState{
public:
    virtual void handleWallCollision(Ghost& ghost,Pacman& pacman) = 0;
    virtual void handleWallCollision(Door& door,Pacman& pacman) = 0;
    virtual ~PacmanState() {}
};

class SuperPacmanState: public PacmanState {
public:
    void handleWallCollision(Ghost& ghost,Pacman& pacman) override ;
    void handleWallCollision(Door& door,Pacman &pacman) override ;

};

class NormalPacman: public PacmanState {
public:
    void handleWallCollision(Ghost& ghost,Pacman& pacman) override;
    void handleWallCollision(Door& door,Pacman& pacman) override;
};
