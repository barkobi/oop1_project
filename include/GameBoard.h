#include <SFML/Graphics.hpp>
#include "../include/GameLevel.h"
#include "fstream"
#include <vector>
#include "filesystem"

class GameBoard {
public:
    GameBoard();

    ~GameBoard();

    std::string exec(std::string command);

    void createBoard();

    sf::RectangleShape getTile(int row, int col) const;

    int getRows();

    int getCols();
/*
    // getters / setters:
    GameLevel getLevel() const;

    // functions:
    bool loadNextLevel();
    void removeChar(Location location);
    void drawBoard()const;
    void drawChar(Location location, char symbol)const;
    void levelDetails(int score,int life, int remain_cookie, int superPacMov) const;
    bool restartLevel();*/
private:
    GameLevel m_level;
    std::vector<std::ifstream> m_board_file;
    std::vector<std::vector<sf::RectangleShape>> m_board;
    std::vector<std::string> m_fileNames;
    int m_rows, m_cols;
    float m_matrixStart;

};