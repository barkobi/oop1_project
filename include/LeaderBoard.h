#pragma once

#include <string>
#include "fstream"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "SFML/Graphics.hpp"
#include "ResourcesManager.h"

// use to modify leaders from the board
struct Leader{
    std::string name;
    int score;
};

class LeaderBoard {
public:
    // constructor / destructor:
    LeaderBoard(sf::RenderWindow &window);
    ~LeaderBoard();


    // functions:
    void print();
    void addScore(int score);
    void printWhileEnterName();

private:
    // members:
    std::fstream m_file;
    Leader m_leaders[10];
    sf::RectangleShape m_backGround;
    sf::RenderWindow &m_window;
    sf::Text m_title;
    sf::Text m_leaderNames[10];
    sf::Text m_leaderScores[10];
    sf::Font m_font;
    std::string m_string;

    //functions:
    void load();
    void updateFile();
    void loadDataToString();
};