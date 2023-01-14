#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "filesystem"
#include "ResourcesManager.h"
#include "objects/GameObject.h"
#include "Level.h"

struct Bounds{
    float topLeftX;
    float topLeftY;
    float BottomRightX;
    float BottomRightY;
    float tile;
};

class GameBoard {
public:
    GameBoard();

    Level &getLevel();

    sf::RectangleShape getTile(int row, int col) const;

    void draw(sf::RenderWindow &window) const;

    // functions:
    bool loadNextLevel();
    bool restartGame();
    Bounds &getBoardBounds();
    bool checkFinishGame();
    std::vector<std::vector<sf::RectangleShape>> getMatrix();

private:
    // members
    std::vector<std::vector<sf::RectangleShape>> m_matrix;
    Level m_level;
    int m_current_level = 1;
    int m_total_levels;
    struct Bounds m_bounds;

    // function
    void createBoard();
    void load_levels_files();
    std::string read_files(std::string command);
};
