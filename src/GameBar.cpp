#include "GameBar.h"
#include "iostream"
GameBar::GameBar(sf::RenderWindow& window) : m_window(window),m_gametime(60){
    m_font.loadFromFile("PressStart2P.ttf");
    int prevloc = 0;
    for(int i = 0;i < 4;i++)
    {
        m_Texts[i].setFillColor(sf::Color::White);
        m_Texts[i].setFont(m_font);
        m_Texts[i].setString(texts[i]);
        m_Texts[i].setCharacterSize(25);
        m_Texts[i].setPosition(100 + prevloc,30);
        prevloc = m_Texts[i].getPosition().x + m_Texts[i].getGlobalBounds().width + 120;
    }
    m_gameTimer.restart().asSeconds();
}

void GameBar::drawStats() {
    for(int i = 0;i < 4;i++)
        m_window.draw(m_Texts[i]);

    m_window.display();
}

void GameBar::updateGameBar(int stats[]) {
    std::stringstream stringtonum;
    for(int i = 0;i < 3;i++)
    {
        stringtonum.str("");
        stringtonum << stats[i];
        m_Texts[i].setString(texts[i] + stringtonum.str().c_str());

    }

    if(m_gameTimer.getElapsedTime().asSeconds() >= 1){
        m_gametime--;
        m_gameTimer.restart().asSeconds();
    }
    stringtonum.str("");
    stringtonum << m_gametime;
    m_Texts[3].setString(texts[3] + stringtonum.str().c_str());

    if(m_gametime == 0)
    {
        Event event(TimeOver ,0);
        EventLoop::instance().addEvent(event);
    }
    drawStats();
}

void GameBar::resetClock() {
    m_gametime = 60;
}

void GameBar::addTime() {
    m_gametime += 15;
}
