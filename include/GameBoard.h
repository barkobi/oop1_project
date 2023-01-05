#include <SFML/Graphics.hpp>
#include "fstream"
#include <vector>
#include "filesystem"
#include "ResourcesManager.h"
#include "Object.h"

class GameBoard {
public:
    GameBoard();

    ~GameBoard();

    std::string exec(std::string command);

    void createBoard();

    sf::RectangleShape getTile(int row, int col) const;

    int getRows();

    int getCols();
    void draw(sf::RenderWindow* window) const;

    void LoadLevel();
    sf::Texture* charToTexture(const char c);

/*
    // functions:
    bool loadNextLevel();
    void drawChar(Location location, char symbol)const;
    void levelDetails(int score,int life, int remain_cookie, int superPacMov) const;
    bool restartLevel();*/
private:
    std::vector<std::ifstream> m_board_file;
    std::vector<std::vector<sf::RectangleShape>> m_board;
    std::vector<std::string> m_fileNames;
    int m_rows, m_cols;
    int m_index;
    float m_matrixStart;
    Object **m_objArr;

};