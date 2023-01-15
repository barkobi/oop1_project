#pragma once
#include <SFML/Graphics.hpp>
#include "../include/GameBoard.h"
#include <vector>
#include <algorithm>
#include <memory>
#include "Pacman.h"
#include "objects/DynamicObjects/ghosts/Ghost.h"
#include "Key.h"
#include "Wall.h"
#include "Door.h"
#include "GhostFreezeGift.h"
#include "LifeIncGift.h"
#include "SuperPacGift.h"
#include "TimeAddGift.h"
#include "Cookie.h"
#include "EventLoop.h"
#include "RandomGhost.h"
#include "SmartGhost.h"
#include "Brain.h"
#include "GameBar.h"

enum Clocks_t{
    ANIMATIONCLOCK,
    MOVECLOCK,
    GIFTCLOCK
};

enum Stats_t{
    Cookies,
    Points,
    Life
};

class GameController{
public:
    GameController(sf::RenderWindow &window);
    void run();
    void print();
private:
    // functions:
    void modifyBoard();
    void charHandler(char type,int row,int col);
    void handleCollision();
    void handleEvent();
    void nextLevel();
    void openDoor();
    void resetLevel();
    void handleAnimations();


    // members
    std::vector<std::unique_ptr<StaticObject>> m_staticObj;
    std::vector<std::unique_ptr<DynamicObject>> m_dynamicObj;
    sf::RenderWindow &m_window;
    sf::Clock clocks[3];
    GameBoard m_board;
    int stats[3];
    bool backToMenu = false;
    GameBar m_gameBar;
    bool freezed = false;
    bool super = false;
    bool paused = false;
};