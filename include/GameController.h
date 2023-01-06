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
private:
    // functions:
    void ModifyBoard();
    std::unique_ptr<GameObject> charHandler(char type,int row,int col);

    // members
    std::vector<std::unique_ptr<GameObject>> m_objects;
    sf::RenderWindow &m_window;
    GameBoard m_board;
    sf::Clock m_clock;
};