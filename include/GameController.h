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

class GameController{
public:
    GameController(sf::RenderWindow &window);
    void run();
    void print();
    sf::Keyboard::Key keyHandler();
    void handleCollision(GameObject& other);
private:
    // functions:
    void ModifyBoard();
    void charHandler(char type,int row,int col);

    // members
    std::vector<std::unique_ptr<StaticObject>> m_staticObj;
    std::unique_ptr<Pacman> m_pacman;
    std::vector<std::unique_ptr<Ghost>> m_ghosts;
    sf::RenderWindow &m_window;
    GameBoard m_board;
    sf::Clock m_clock;
};