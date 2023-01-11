#include <SFML/Graphics.hpp>
#include "../include/GameBoard.h"
#include <vector>
#include <algorithm>
#include <memory>
#include "Pacman.h"
#include "Ghost.h"
#include "Key.h"
#include "Wall.h"
#include "Door.h"
#include "Gift.h"
#include "Cookie.h"
#include "EventLoop.h"

enum Clocks_t{
    GAMECLOCK,
    ANIMATIONCLOCK,
    MOVECLOCK
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

    // members
    std::vector<std::unique_ptr<StaticObject>> m_staticObj;
    std::vector<std::unique_ptr<DynamicObject>> m_dynamicObj;
    sf::RenderWindow &m_window;
    sf::Clock clocks[3];
    GameBoard m_board;
    int m_cookies_on_board;
    int m_lives = 3;
    int m_points = 0;
    bool backToMenu = false;
};