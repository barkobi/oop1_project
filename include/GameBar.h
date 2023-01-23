#pragma once
#include "eventLoop.h"
#include "sstream"
#include "SFML/Graphics.hpp"
#include "iostream"
#include "ResourcesManager.h"

/**
 * Game bar class responsible for showing and updating stats ahout the game
 */
class GameBar{
public:
    // C-Tor
    GameBar();
    // Functions
    void updateGameBar(int stats[]);
    void drawStats(sf::RenderWindow &window);
    void resetClock(int time);
    void addTime();
private:
    // members
    sf::Clock m_gameTimer;
    int m_gametime;
    sf::Text m_Texts[4];
    std::string texts[4] = {"Remaining Coins : ","Points : ","Life : ","Remaining Time : "};
};
