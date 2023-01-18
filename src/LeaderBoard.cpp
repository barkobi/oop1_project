#include "LeaderBoard.h"
#include "sstream"
/**
 * open the leaderBoard file and load the leaders
 */
LeaderBoard::LeaderBoard(sf::RenderWindow &window, bool editMode) :m_window(window), editMode(editMode){
    initComponents();
    load();
    print();
    if(!editMode)
        eventHandler();
}

void LeaderBoard::initComponents() {
    m_backGround.setSize(sf::Vector2f (WINDOW_WIDTH,WINDOW_HEIGHT));
    m_backGround.setTexture(ResourcesManager::instance().getBackground());
    m_title.setFont(ResourcesManager::instance().getFont());
    m_title.setCharacterSize(60);
    m_title.setString("Leader Board :");
    m_title.setPosition(sf::Vector2f(WINDOW_WIDTH/2,WINDOW_HEIGHT*0.1));
    m_title.setOrigin(m_title.getGlobalBounds().width/2,m_title.getGlobalBounds().height/2);
    m_arrow.setString("->");
    m_arrow.setFont(ResourcesManager::instance().getFont());

    for(int i = 0;i < 10;i++){
        m_leaderNames[i].setFont(ResourcesManager::instance().getFont());
        m_leaderScores[i].setFont(ResourcesManager::instance().getFont());
    }
    pt_text.setFont(ResourcesManager::instance().getFont());
    pt_text.setString("pt");
    pt_text.setCharacterSize(m_leaderScores[0].getCharacterSize()*0.7);
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
    m_file.open("leaderBoard.txt");
    int i=0;
    if(m_file.is_open()){
        for (i = 0 ; i < 10 ; i++){
            m_file >> m_leaders[i].score;
            m_file >> m_leaders[i].name;
            if (m_file.fail() || m_file.eof()){
                m_file.clear();
                break;
            }
        }
    }
    if (i < 10){
        for (int j = i ; j < 10 ; j++){
            m_leaders[j].name = ".";
            m_leaders[j].score = 0;
        }
    }

    loadDataToString();
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
        auto add = sf::Vector2f(m_leaderScores[i].getGlobalBounds().width+10,m_leaderScores[i].getGlobalBounds().height-pt_text.getGlobalBounds().height);
        pt_text.setPosition(m_leaderScores[i].getPosition() + add);
        m_window.draw(pt_text);
    }
    if(editMode)
        m_window.draw(m_arrow);
//        if(m_arrowClock.getElapsedTime().asSeconds() > 0.3){
//            m_arrowClock.restart();
    m_window.display();
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
    }
    m_leaders[pos] = newLeader;

    loadDataToString();
    m_arrow.setPosition(m_leaderNames[pos].getPosition().x- m_arrow.getGlobalBounds().width-20, m_leaderNames[pos].getPosition().y);

    print();
    addScoreEventHandler(pos);
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
    std::stringstream stringtonum;
    float prevloc = m_title.getPosition().y + (m_title.getGlobalBounds().height)*2.5;
    for(int i = 0;i< 10;i++){
        std::string str = m_leaders[i].name;
        stringtonum.str("");
        stringtonum << m_leaders[i].score;
        m_leaderNames[i].setString(str);
        m_leaderNames[i].setPosition(sf::Vector2f(WINDOW_WIDTH*0.25, prevloc));

        m_leaderScores[i].setString(stringtonum.str().c_str());
        m_leaderScores[i].setPosition(sf::Vector2f(WINDOW_WIDTH*0.75, prevloc));
        prevloc += m_leaderScores[i].getGlobalBounds().height*2.5;
    }
}

void LeaderBoard::eventHandler() {
    while(m_window.isOpen()){
        auto event = sf::Event{};
        m_window.pollEvent(event);
        if(event.type == event.KeyPressed){
            if(event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)
                break;
        }
    }
}

void LeaderBoard::addScoreEventHandler(const int pos){
    m_arrowClock.restart().asSeconds();
    print();
    while(m_window.isOpen()){
        auto event = sf::Event{};
        m_window.waitEvent(event);
        if(event.type == sf::Event::Closed)
            m_window.close();
        if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::Escape)
            return;
        if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::BackSpace){
            if (!m_leaders[pos].name.empty()){
                m_leaders[pos].name.pop_back();
                std::cout << m_leaders[pos].name << "\n";
                m_leaderNames[pos].setString(m_leaders[pos].name);
                print();
            }
            continue;
        }
        if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::Enter){
            editMode=false;
            updateFile();
            print();
            eventHandler();
            return;
        }
        if(event.type == sf::Event::TextEntered){
            if(event.text.unicode == ' ' ||event.text.unicode == '\b')
                continue;
            if(m_leaders[pos].name.size() < 10)
                m_leaders[pos].name += event.text.unicode;
            m_leaderNames[pos].setString(m_leaders[pos].name);
            print();
        }
    }
}
