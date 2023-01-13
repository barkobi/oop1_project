#pragma once
#include "eventLoop.h"
#include "sstream"
#include "SFML/Graphics.hpp"
class GameBar{
public:
    GameBar(sf::RenderWindow& window);
    void updateGameBar(int stats[]);
    void drawStats();
    void resetClock();
    void addTime();
private:
    sf::RenderWindow& m_window;
    sf::Clock m_gameTimer;
    int m_gametime;
    sf::Text m_Texts[4];
    sf::Font m_font;
    std::string texts[4] = {"Remaining Cookies : ","Points : ","Life : ","Remaining Time : "};
};
