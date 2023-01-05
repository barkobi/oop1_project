#include <SFML/Graphics.hpp>
#include "fstream"
#include <vector>
#include "filesystem"
#include "ResourcesManager.h"
#include "GameObject.h"
#include "Level.h"

class GameBoard {
public:
    GameBoard();
    ~GameBoard();

    Level &getLevel();

    sf::RectangleShape getTile(int row, int col) const;

    void draw(sf::RenderWindow* window) const;

    // functions:
    void loadNextLevel();
    void restartGame();


private:
    std::ifstream m_board_file;
    std::vector<std::vector<sf::RectangleShape>> m_matrix;
    Level m_level;

    void createBoard();
};
