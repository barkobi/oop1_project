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
    LeaderBoard(sf::RenderWindow &window, bool editMode = false);
    ~LeaderBoard();


    // functions:
    void print();
    void addScore(int score);

private:
    // members:
    std::fstream m_file;
    Leader m_leaders[10];
    sf::RectangleShape m_backGround;
    sf::RenderWindow &m_window;
    sf::Text m_title;
    sf::Text m_leaderNames[10];
    sf::Text m_leaderScores[10];
    sf::Text m_arrow;
    bool editMode;
    sf::Clock m_arrowClock;

    //functions:
    void initComponents();
    void load();
    void updateFile();
    void loadDataToString();
    void enterName(int loc);
    void eventHandler();
    void addScoreEventHandler(const int pos);
};