#pragma once
#include "iostream"
#include "eventLoop.h"
class Ghost;
class Door;
class PacmanState{
public:
    virtual bool handleWallCollision(Ghost& ghost) = 0;
    virtual bool handleWallCollision(Door& door) = 0;
    virtual ~PacmanState() {}
};

class SuperPacmanState: public PacmanState {
public:
    bool handleWallCollision(Ghost& ghost) override {
        return true;
    }
    bool handleWallCollision(Door& door) override {
        return true;
    }

};

class NormalPacman: public PacmanState {
public:
    bool handleWallCollision(Ghost& ghost) override {
        EventLoop::instance().addEvent(Event(CollapseWithGhost));
        return false;
    }
    bool handleWallCollision(Door& door) override {
        return false;
    }
};