#include "../include/GameLevel.h"
#include <fstream>
#include <iostream>

GameLevel::GameLevel() = default;

/**
 * @return get map width
 */
int GameLevel::getCols() const { return m_cols;}

/**
 * @return get map height
 */
int GameLevel::getRows() const{return m_rows;}


/**
 * load the next map from the file
 * @param board_file the file to load from
 * @return is the level loaded successfully
 */
bool GameLevel::load_level(std::ifstream &board_file) {
    board_file >> m_rows >> m_cols;
    setOnBoard(1); // set pac on board.
    char c;
    for(int row = 0;row < m_rows;row++) {
        c = char(board_file.get());
        for(int col = 0;col < m_cols;col++)
        {
            c = char(board_file.get());
            if(c != ' ') {
//                sf::Texture* objectTexture = charToTexture(c); // convert char to texture.
//                m_objArr[row][col].setTexture(objectTexture); // set on board
//                m_objArr[row][col].setPosition(m_board[row][col].getPosition(),c); // set position.
            }

        }
    }
    //validateLevel();
    return true;
}

bool GameLevel::setOnBoard(int flag) {
    isOnBoard = flag;
}

/**
 * validate the level.
 * valid level include:
 * 1 pacman
 * 0 super pacmans
 * at least 1 cookie
 * equal number of doors and keys
 */
 /*
void GameLevel::validateLevel(){
    int cookies=0, doors=0, keys=0 ,packman = 0, super_pm = 0;

    for(int row=0 ; row<m_height ; row++){
        for(int col=0 ; col<m_width ; col++){
            switch (m_map[row][col]) {
                case PACMAN_S:
                    packman++;
                    break;
                case SUPER_PM_S:
                    super_pm++;
                    break;
                case DOOR_S:
                    doors++;
                    break;
                case KEY_S:
                    keys++;
                    break;
                case COOKIE_S:
                    cookies++;
                    break;
            }
        }
    }
    if (cookies < 1 || (doors != keys) || (super_pm != 0) || (packman != 1) ){
        std::cerr << "Board file is not valid\n";
        exit(EXIT_FAILURE);
    }
}
*/