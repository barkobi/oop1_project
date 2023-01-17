#include "LeaderBoard.h"
#include "sstream"
/**
 * open the leaderBoard file and load the leaders
 */
LeaderBoard::LeaderBoard(sf::RenderWindow &window) :m_window(window){
    m_file.open("leaderBoard.txt");
    m_backGround.setSize(sf::Vector2f (WINDOW_WIDTH,WINDOW_HEIGHT));
    m_backGround.setTexture(ResourcesManager::instance().getBackground());
    m_title.setFont(ResourcesManager::instance().getFont());
    m_title.setString("Leader Board :");
    m_title.setPosition(sf::Vector2f(WINDOW_WIDTH/4,WINDOW_HEIGHT/16));
    m_title.setScale(3,3);
    for(int i = 0;i < 10;i++){
        m_leaderNames[i].setFont(ResourcesManager::instance().getFont());
        m_leaderScores[i].setFont(ResourcesManager::instance().getFont());
    }

    load();

    loadDataToString();
}

/**
 * Close the file.
 */
LeaderBoard::~LeaderBoard() {
    m_file.close();
}

/**
 * load the leaders from the file.
 */
void LeaderBoard::load() {
    int i;
    for(i=0 ; i<10 ; i++){
        m_file >> m_leaders[i].score;
        m_file >> m_leaders[i].name;
        if(m_file.fail() || m_file.eof())
            break;
    }
    if(i<10){
        m_file.clear();
        for(int j=i ; j<10 ; j++){
            m_leaders[j].name = ".";
            m_leaders[j].score = 0;
        }
    }
}

/**
 * print the leader board to the console.
 */
void LeaderBoard::print() {
    m_window.clear();
    m_window.draw(m_backGround);
    m_window.draw(m_title);
    for(int i = 0;i < 10;i++){
        m_window.draw(m_leaderNames[i]);
        m_window.draw(m_leaderScores[i]);
    }

    m_window.display();
    while(m_window.isOpen()){
        auto eventwait = sf::Event{};
        m_window.waitEvent(eventwait);
        if(eventwait.type == eventwait.KeyPressed)
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                break;
    }

}

/**
 * add new score to the leaderboard, will added only if in top 10.
 * @param score the new score to add.
 */

void LeaderBoard::addScore(int score){
    int pos = 0;
    for(int i=0 ; i<10 && m_leaders[i].score>=score ; i++, pos++);

    if(pos==10)
        return;

    Leader newLeader;
    newLeader.score = score;
    newLeader.name = "";

    for(int i=9 ; i>pos ; i--){
        m_leaders[i] = m_leaders[i-1];
        m_leaderNames[i] = m_leaderNames[i-1];
        m_leaderScores[i] = m_leaderScores[i-1];
    }
    m_leaders[pos] = newLeader;

    loadDataToString();

    printWhileEnterName();
    while(m_window.isOpen()){
        auto eventwait = sf::Event{};
        m_window.waitEvent(eventwait);
        if(eventwait.type == sf::Event::TextEntered)
        {
            m_leaders[pos].name += eventwait.text.unicode;
        }
        if(eventwait.type == sf::Event::KeyPressed)
            if(eventwait.key.code == sf::Keyboard::Return)
                break;
        if(eventwait.type == sf::Event::KeyPressed)
            if(eventwait.key.code == sf::Keyboard::BackSpace)
                if (!m_leaders[pos].name.empty())
                    m_leaders[pos].name.pop_back();

        m_leaderNames[pos].setString(m_leaders[pos].name);
        printWhileEnterName();
    }
    updateFile();
}

/**
 * update the file with the new leader.
 */
void LeaderBoard::updateFile() {
    m_file.seekg(0);
    for(int i=0 ; i<10 ; i++) {
        m_file << m_leaders[i].score << " " << m_leaders[i].name << std::endl;
    }

}

void LeaderBoard::loadDataToString() {
    std::cout << "in load\n";
    std::stringstream stringtonum;
    float prevloc = 50;
    for(int i = 1;i< 10;i++)
    {
        std::string spacestring = " ";
        m_string = m_leaders[i].name;
        stringtonum.str("");
        stringtonum << m_leaders[i].score;
        m_leaderNames[i].setString(m_string);
        m_leaderNames[i].setPosition(sf::Vector2f(WINDOW_WIDTH/4,WINDOW_HEIGHT/8 + prevloc));
        m_leaderScores[i].setString(stringtonum.str().c_str());
        m_leaderScores[i].setPosition(sf::Vector2f(WINDOW_WIDTH/4 + (m_title.getGlobalBounds().width - m_leaderScores[i].getGlobalBounds().width),WINDOW_HEIGHT/8 + prevloc));
        prevloc += m_leaderNames[i].getGlobalBounds().height + 50;
    }
}

void LeaderBoard::printWhileEnterName() {
    m_window.clear();
    m_window.draw(m_backGround);
    m_window.draw(m_title);
    for(int i = 0;i < 10;i++){
        m_window.draw(m_leaderNames[i]);
        m_window.draw(m_leaderScores[i]);
    }

    m_window.display();
}
