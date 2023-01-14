#include "GameBar.h"

GameBar::GameBar() : m_gametime(60){
    int prevloc = 0;
    for(int i = 0;i < 4;i++)
    {
        m_Texts[i].setFillColor(sf::Color::White);
        m_Texts[i].setFont(ResourcesManager::instance().getFont());
        m_Texts[i].setString(texts[i]);
        m_Texts[i].setCharacterSize(30);
        m_Texts[i].setPosition(WINDOW_WIDTH*0.05 + prevloc,30);
        prevloc = m_Texts[i].getPosition().x + (m_Texts[i].getGlobalBounds().width) + WINDOW_WIDTH*0.05;
    }
    m_gameTimer.restart().asSeconds();
}

void GameBar::drawStats(sf::RenderWindow &window){
    for(int i = 0;i < 4;i++)
        window.draw(m_Texts[i]);
}

void GameBar::updateGameBar(int stats[]){
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
        EventLoop::instance().addEvent(Event(TimeOver));
    }
}

void GameBar::resetClock() {
    m_gametime = 60;
}

void GameBar::addTime() {
    m_gametime += 15;
}
