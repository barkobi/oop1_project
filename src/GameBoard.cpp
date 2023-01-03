#include "../include/GameBoard.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include "../resources/Consts.h"

/**
 * create a board, open the board file and load the first level.
 */
GameBoard::GameBoard() {
    m_level = GameLevel();
    auto str = exec("find . -name \"*.txt\"");
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    auto cutStr = strtok(cstr, "\n");
    while (cutStr != NULL) {
        m_fileNames.push_back(cutStr);
        cutStr = strtok(NULL, " \n\0");
    }


    std::ifstream file;
    file.open(m_fileNames[0]);
//    m_board_file.push_back(file);
    if (!m_level.load_level(file)) {
        std::cerr << "Cannot read Board file\n";
        exit(EXIT_FAILURE);
    }
    m_rows = m_level.getRows();
    m_cols = m_level.getCols();
    createBoard();
}

std::string GameBoard::exec(std::string command) {
    char buffer[128];
    std::string result = "";

    // Open pipe to file
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "popen failed!";
    }

    // read till end of process:
    while (!feof(pipe)) {

        // use buffer to read and add to result
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }

    pclose(pipe);
    return result;
}

/**
 * close the board file
 */
GameBoard::~GameBoard() {
    for (int i = 0; i < m_board_file.size(); ++i) {
        m_board_file[i].close();
    }

}

void GameBoard::createBoard() {
//    m_objArr = new Objects*[m_rows];
//    for(int row = 0;row < m_rows;row++)
//        m_objArr[row] = new Objects[m_cols];

//    m_num_keys = m_num_doors = m_pacBoard = m_last_i = m_last_j = 0;
    m_board.clear();
    // calculate tile size with window vars.
    float tileSize = ((WINDOW_WIDTH - MENU_WIDTH) / (std::max(m_cols, m_rows)) / 1.8);
    float startPoint = ((WINDOW_WIDTH - MENU_WIDTH) / 2) - ((tileSize * m_cols) / 2);
    m_matrixStart = (WINDOW_HEIGHT / 2) - (tileSize * m_rows) / 1.85;

    // create the rectangle matrix.
    for (int row = 0; row < m_rows; row++) {
        auto spec_line = std::vector<sf::RectangleShape>();
        for (int col = 0; col < m_cols; col++) {
            auto r = sf::RectangleShape();
            r.setOutlineThickness(1);
            r.setSize(sf::Vector2f(tileSize - 1, tileSize - 1));
            r.setPosition(float(col * (tileSize + 1) + startPoint), float(row * (tileSize + 1) + m_matrixStart));
            r.setFillColor(sf::Color(100, 190, 190));
            r.setOutlineColor(sf::Color(100, 190, 190));
            spec_line.push_back(r);
        }
        m_board.push_back(spec_line);
    }
}

sf::RectangleShape GameBoard::getTile(int row, int col) const {
    return m_board[row][col];
}

int GameBoard::getRows() {
    return m_rows;
}

int GameBoard::getCols() {
    return m_cols;
}


/**
 * load the next level.
 * @return is the level loaded successfully

bool GameBoard::loadNextLevel() {

}

/*
bool GameBoard::restartLevel() {
    m_board_file.clear();
    m_board_file.seekg(0, std::ios::beg);
    if(!m_level.load_level(&m_board_file)){
        std::cerr << "Cannot restart\n";
        exit(EXIT_FAILURE);
    }
}
/**
 * @return get the current level

Level Board::getLevel() const {return m_level;}

/**
 * draw the board to the console

void Board::drawBoard() const{
    std::system("cls");
    for(int row=0 ; row< m_level.getHeight() ; row++){
        std::cout << m_level.getMapRow(row) << std::endl;
    }
}

/**
 * remove char from the map, insert space in the location
 * @param location the location of the char to remove

void Board::removeChar(Location location) {
    m_level.removeChar(location);
}

/**
 * draw char to the console at given location
 * @param location the location to draw on
 * @param symbol the symbol to draw

void Board::drawChar(Location location, char symbol) const {
    Screen::setLocation(location);
    std::cout << symbol;
}

/**
 * draw the scores and lives.
 * @param score the current score
 * @param life how much lives left

void Board::levelDetails(int score,int life , int remain_cookie, int superPacMov) const{
    Screen::setLocation(Location(m_level.getHeight() + 1, 0));
    std::cout << "Remaining Cookie : " << remain_cookie << " ";
    if(superPacMov != 0)
        std::cout << "Super Pacman Moves Left : " << superPacMov << std::endl;
    std::cout << "Current Score : " << score << " " << "Remaining Life : " << life << std::endl;
}*/
