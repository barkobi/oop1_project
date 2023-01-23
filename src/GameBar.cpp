#include "GameBar.h"

/**
 * create gameBar, calculate each text position.
 */
GameBar::GameBar(){
    int prevloc = 0;
    for(int i = 0;i < 4;i++){
        m_Texts[i].setFillColor(sf::Color::White);
        m_Texts[i].setFont(ResourcesManager::instance().getFont());
        m_Texts[i].setString(texts[i]);
        m_Texts[i].setCharacterSize(30);
        m_Texts[i].setPosition(prevloc,30);
        prevloc+= m_Texts[i].getGlobalBounds().width;
    }
    //add spacing
    float extraSpace = WINDOW_WIDTH - m_Texts[3].getPosition().x - m_Texts[3].getGlobalBounds().width;
    extraSpace /= 5;
    for(int i = 0;i < 4;i++){
        float moveBy = extraSpace * (i+1);
        m_Texts[i].move(moveBy,0);
    }
    m_gameTimer.restart().asSeconds();
}

/**
 * draw the game bar
 * @param window the window to draw on
 */
void GameBar::drawStats(sf::RenderWindow &window){
    for(int i = 0;i < 4;i++)
        window.draw(m_Texts[i]);
}

/**
 * update the texts with a given stats
 * @param stats
 */
void GameBar::updateGameBar(int stats[]){
    std::stringstream stringtonum;
    for(int i = 0;i < 3;i++)
    {
        stringtonum.str("");
        stringtonum << stats[i];
        m_Texts[i].setString(texts[i] + stringtonum.str().c_str());
    }

    if(stats[3] == 1)
        m_gameTimer.restart().asSeconds();

    if(m_gameTimer.getElapsedTime().asSeconds() >= 1){
        m_gametime--;
        m_gameTimer.restart().asSeconds();
    }

    stringtonum.str("");
    stringtonum << m_gametime;
    m_Texts[3].setString(texts[3] + stringtonum.str().c_str());

    if(m_gametime == 0)
        EventLoop::instance().addEvent(Event(TimeOver));

}

void GameBar::resetClock(int time) {
    m_gametime = time;
}

void GameBar::addTime() {
    m_gametime += 15;
}
