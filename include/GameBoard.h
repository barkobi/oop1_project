#include <SFML/Graphics.hpp>
#include <vector>
#include "filesystem"
#include "ResourcesManager.h"
#include "objects/GameObject.h"
#include "Level.h"

class GameBoard {
public:
    GameBoard();

    Level &getLevel();

    sf::RectangleShape getTile(int row, int col) const;

    void draw(sf::RenderWindow &window) const;

    // functions:
    bool loadNextLevel();
    bool restartGame();


private:
    // members
    std::vector<std::vector<sf::RectangleShape>> m_matrix;
    Level m_level;
    int m_current_level = 1;
    int m_total_levels;

    // function
    void createBoard();
    void load_levels_files();
    std::string read_files(std::string command);
};
