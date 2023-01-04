#include <SFML/Graphics.hpp>
#include "../include/GameBoard.h"
class GameController{
public:
    GameController(sf::RenderWindow &window);
    void run();
    void print();
private:
    sf::RenderWindow *m_window;
    GameBoard m_board;
    sf::Clock m_clock;
};