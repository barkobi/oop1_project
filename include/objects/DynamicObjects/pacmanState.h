#pragma once
#include "eventLoop.h"
#include "iostream"
class Ghost;
class Door;
class Pacman;

/**
 * abstarct class of pacman state
 */
class PacmanState{
public:
    // virtual functions and D-tor
    virtual void handleWallCollision(Ghost& ghost,Pacman& pacman) = 0;
    virtual void handleWallCollision(Door& door,Pacman& pacman) = 0;
    virtual ~PacmanState() {}
};

/**
 * super pacman state class heiress from pacman state for handling special collisions
 */
class SuperPacmanState: public PacmanState {
public:
    // functions
    void handleWallCollision(Ghost& ghost,Pacman& pacman) override ;
    void handleWallCollision(Door& door,Pacman &pacman) override ;

};

/**
 * pacman state class heiress from pacman state for handling regular collisions
 */
class NormalPacman: public PacmanState {
public:
    // functions
    void handleWallCollision(Ghost& ghost,Pacman& pacman) override;
    void handleWallCollision(Door& door,Pacman& pacman) override;
};
