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
#include "LeaderBoard.h"
#include "../values/Points.h"

// enums
enum Clocks_t{
    ANIMATIONCLOCK,
    MOVECLOCK,
    GIFTCLOCK,
};

enum Stats_t{
    Cookies,
    Points,
    Life,
    isStopped
};

/**
 * the main class that managing the game
 */
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
    void gameOverOrDone(std::string msg[2]);
    void reloadLevel();
    void pressedSpaceHandler();
    void setMassageTexts(std::string messages[2]);

    // members
    std::vector<std::unique_ptr<StaticObject>> m_staticObj;
    std::vector<std::unique_ptr<DynamicObject>> m_dynamicObj;
    sf::RenderWindow &m_window;
    sf::Clock clocks[4];
    sf::Text msgTexts[2];
    std::string gameStrings[4] = {"Paused","Press Space To Continue",};
    GameBoard m_board;
    int stats[4];
    GameBar m_gameBar;
    bool freezed = false;
    bool super = false;
    bool paused = false;
    bool isGameOver = false;
};