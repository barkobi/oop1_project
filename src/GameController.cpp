#include "GameController.h"
#include "SoundFlip.h"
#include "cmath"

GameController::GameController(sf::RenderWindow &window)
    : m_window(window), m_board(GameBoard()){
    int nextY = 0;
    gameTexts[0].setCharacterSize(80);
    gameTexts[1].setCharacterSize(50);
    gameTexts[2].setCharacterSize(80);
    gameTexts[3].setCharacterSize(50);

    for(int i = 0;i < 2;i++){
        gameTexts[i].setFont(ResourcesManager::instance().getFont());
        gameTexts[i+2].setFont(ResourcesManager::instance().getFont());
        gameTexts[i].setString(gameStrings[i]);
        gameTexts[i+2].setString(gameStrings[i+2]);
        gameTexts[i].setPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT/2 + nextY*1.5);
        gameTexts[i+2].setPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT/2 + nextY*1.5);
        gameTexts[i].setOrigin(gameTexts[i].getGlobalBounds().width/2,gameTexts[i].getGlobalBounds().height/2);
        gameTexts[i+2].setOrigin(gameTexts[i+2].getGlobalBounds().width/2,gameTexts[i+2].getGlobalBounds().height/2);
        nextY = gameTexts[i].getGlobalBounds().height;
    }

    stats[Life] = 3;
    stats[Points] = 0;
    stats[Cookies] = 0;
    modifyBoard();
}

void GameController::run(){
    print();
    std::vector<std::vector<int>> bfsRes;
    while(m_window.isOpen()){
        if(!paused)
            stats[isStopped] = 0;
        if(auto event = sf::Event{}; m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return;
            if (event.type == sf::Event::MouseButtonReleased)
                SoundFlip::instance().checkIfContains(event.mouseButton);
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    if(isGameOver){
                        if(!ResourcesManager::instance().isBGMusicPlaying()){
                            ResourcesManager::instance().stopSound(GAME_DONE);
                            ResourcesManager::instance().playBackgroundMusic();
                        }
                        auto leader = LeaderBoard(m_window, true);
                        leader.addScore(stats[1]);
                        return;
                    }
                    paused = !paused;
                    if (paused) {
                        stats[isStopped] = 1;
                    }
                }
            }
        }
        bfsRes = Brain::calculateBFS(Brain::addObjectsToMap(m_dynamicObj[0]->getSprite().getPosition(), m_board.getLevel().getMap(), m_board.getTile(0,0).getGlobalBounds().height ,
                                                                 m_board.getTile(0,0).getPosition(),m_dynamicObj[0]->getSprite().getGlobalBounds().width));
        float deltaTime = clocks[MOVECLOCK].restart().asSeconds();
        for(int i=0 ; i<m_dynamicObj.size() ; i++){
            if((i > 0 && freezed) || paused)
                break;
            m_dynamicObj[i]->move(deltaTime,m_board.getBoardBounds(), bfsRes);
        }
        handleCollision();
        handleEvent();
        handleAnimations();
        m_gameBar.updateGameBar(stats);
        print();
    }
}

void GameController::handleEvent() {
    if(clocks[GIFTCLOCK].getElapsedTime().asSeconds() > 5){
        freezed = false;
        if(super){
            for(int i=0 ; i<m_dynamicObj.size() ; i++)
                m_dynamicObj[i]->setTextureRegular();
            super = false;
        }
    }

    while(EventLoop::instance().hasEvent()){
        auto event = EventLoop::instance().popEvent();
        switch (event.getEventType()){
            case CollapseWithGhost:
            {
                ResourcesManager::instance().playSound(COLLAPSE_WITH_GHOST);
                stats[Life]--;
                if(stats[Life] == 0)
                    EventLoop::instance().addEvent(Event(GameOver));
                resetLevel();
                break;
            }
            case EatCookie:{
                ResourcesManager::instance().playSound(CHEW_SOUND);
                stats[Cookies]--;
                if(stats[Cookies] == 0)
                    EventLoop::instance().addEvent(Event(LevelEnd));
                break;
            }
            case GotLifeGift:
                stats[Life]++;
                break;
            case GotSuperGift:
                m_dynamicObj[0]->setTexture(ResourcesManager::instance().getObjectTexture(SUPERPACMAN));
                for(int i=1 ; i<m_dynamicObj.size() ; i++)
                    m_dynamicObj[i]->setTexture(ResourcesManager::instance().getObjectTexture(SUPERPMGHOST));
                clocks[GIFTCLOCK].restart().asSeconds();
                super = true;
                break;
            case GotTimeAddGift:
                m_gameBar.addTime();
                break;
            case GotGhostFreezeGift:
                clocks[GIFTCLOCK].restart().asSeconds();
                freezed = true;
                break;
            case GotKey:{
                openDoor();
                break;
            }
            case GameOver:{
                printf("Game Over!\n");
                ResourcesManager::instance().playSound(GAME_OVER);
                std::string msg[2] = {"Game Over!", "Better Luck Next Time"};
                gameOverOrDone(msg);
                break;
            }
            case LevelEnd:{
                nextLevel();
                break;
            }
            case GameDone:{
                printf("Game Done!\n");
                ResourcesManager::instance().pauseBackgroundMusic();
                ResourcesManager::instance().playSound(GAME_DONE);
                std::string msg[2] = {"Game Done!", "You Are The Winner"};
                gameOverOrDone(msg);
                break;
            }
            case TimeOver:
                if(!paused)
                    EventLoop::instance().addEvent(Event(GameOver));
                else;
                break;
        }
        stats[Points]+=event.getPoints();
    }
}

void GameController::print() {
    m_window.clear();
    auto background = sf::RectangleShape();
    background.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
    background.setTexture(ResourcesManager::instance().getBackground());
    m_window.draw(background);
    m_gameBar.drawStats(m_window);
    m_board.draw(m_window);
    for(int obj = 0;obj < m_staticObj.size();obj++){
        m_staticObj[obj]->draw(&m_window);
    }
    for(int obj = 0;obj < m_dynamicObj.size();obj++){
        m_dynamicObj[obj]->draw(&m_window);
    }

    SoundFlip::instance().draw(m_window);

    if(paused){
        sf::RectangleShape fadedBackground;
        fadedBackground.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
        fadedBackground.setFillColor(sf::Color(0,0,0,90));

        m_window.draw(fadedBackground);

        for(int i = 0;i < 2;i++)
            m_window.draw(gameTexts[i]);
    }
    m_window.display();
}

void GameController::modifyBoard() {
    m_dynamicObj.clear();
    m_staticObj.clear();
    auto map = m_board.getLevel().getMap();
    for(int row = 0;row < map.size();row++){
        for(int col = 0;col < map[row].length();col++){
            if (map[row][col] != ' '){
                charHandler(map[row][col], row, col);
                if(map[row][col]!= WALL_S)
                    m_board.getLevel().removeChar(row,col);
            }
        }
    }
}

void GameController::charHandler(char type,int row,int col){
    auto tile = m_board.getTile(row,col);
    switch (type) {
        case PACMAN_S:{
            m_dynamicObj.push_back(std::make_unique<Pacman>(tile.getPosition(),0.7,tile.getGlobalBounds().width));
            std::swap(m_dynamicObj.front(),m_dynamicObj.back());
            break;
        }
        case GHOST_S:{
            static bool ghost = false;
            if(ghost)
                m_dynamicObj.push_back(std::make_unique<RandomGhost>(tile.getPosition(),0.75,tile.getGlobalBounds().width));
            else
                m_dynamicObj.push_back(std::make_unique<SmartGhost>(tile.getPosition(),0.75,tile.getGlobalBounds().width));
            ghost = !ghost;
            break;
        }
        case KEY_S:{
            m_staticObj.push_back(std::make_unique<Key>(tile.getPosition(),0.7,tile.getGlobalBounds().width));
            break;
        }
        case DOOR_S:{
            m_staticObj.push_back(std::make_unique<Door>(tile.getPosition(),1,tile.getGlobalBounds().width));
            break;
        }
        case WALL_S:{
            m_staticObj.push_back(std::make_unique<Wall>(tile.getPosition(),1,tile.getGlobalBounds().width));
            break;
        }
        case GIFT_S:{
            static int gift = -1;
            int tmp;
            do{tmp = rand()%4;} while (tmp==gift);
            gift = tmp;
            switch (gift) {
                case 0:
                    m_staticObj.push_back(std::make_unique<TimeAddGift>(tile.getPosition(),0.7,tile.getGlobalBounds().width));
                    break;
                case 1:
                    m_staticObj.push_back(std::make_unique<SuperPacGift>(tile.getPosition(),0.7,tile.getGlobalBounds().width));
                    break;
                case 2:
                    m_staticObj.push_back(std::make_unique<GhostFreezeGift>(tile.getPosition(),0.7,tile.getGlobalBounds().width));
                    break;
                case 3:
                    m_staticObj.push_back(std::make_unique<LifeIncGift>(tile.getPosition(),0.7,tile.getGlobalBounds().width));
                    break;
            }
            break;
        }
        case COOKIE_S:{
            stats[Cookies]++;
            m_staticObj.push_back(std::make_unique<Cookie>(tile.getPosition(),0.5,tile.getGlobalBounds().width));
            break;
        }
    }
}

void GameController::handleCollision() {
    for(int dynamicObj=0 ; dynamicObj<m_dynamicObj.size() ; dynamicObj++){
        for(int otherDynamic=0 ; otherDynamic<m_dynamicObj.size() ; otherDynamic++){
            if(m_dynamicObj[dynamicObj]->checkCollision(*(m_dynamicObj[otherDynamic])))
                m_dynamicObj[dynamicObj]->handleCollision(*(m_dynamicObj[otherDynamic]));
        }
        for(int staticObj=0 ; staticObj<m_staticObj.size() ; staticObj++){
            if(m_dynamicObj[dynamicObj]->checkCollision(*(m_staticObj[staticObj])))
                m_dynamicObj[dynamicObj]->handleCollision(*(m_staticObj[staticObj]));
        }
    }
    std::erase_if(m_staticObj, [](const auto& obj) { return obj->needToDelete();});
}

void GameController::nextLevel() {
    if(m_board.checkFinishGame()){
        EventLoop::instance().addEvent(Event(GameDone));
        return;
    }
    sf::RectangleShape fadedBackground;
    fadedBackground.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    fadedBackground.setFillColor(sf::Color(0, 0, 0, 90));

    m_window.draw(fadedBackground);
    m_window.draw(gameTexts[2]);
    m_window.draw(gameTexts[3]);
    m_window.display();
    while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space));

    m_board.loadNextLevel();
    modifyBoard();
    //m_gameBar.resetClock((((m_board.getLevel().getWidth() + m_board.getLevel().getHeight())/2) * stats[Cookies]) / 15);
    m_gameBar.resetClock(60);
}

void GameController::openDoor() {
    int min = WINDOW_WIDTH;
    int index = -1;
    for(int i = 0;i < m_staticObj.size();i++){
        float distance = m_staticObj[i]->checkDistance(m_dynamicObj[0]->getSprite().getPosition());
        if(distance < min){
            min = distance;
            index = i;
        }
    }
    if(index != -1 && min != WINDOW_WIDTH)
        dynamic_cast<Door*>(m_staticObj[index].get())->openDoor();

}

void GameController::resetLevel() {
    for(int i=0 ; i<m_dynamicObj.size() ; i++)
        m_dynamicObj[i]->goToInitialPosition();

}

void GameController::handleAnimations() {
    auto time = clocks[ANIMATIONCLOCK].getElapsedTime().asSeconds();
    if(time > 0.15){
        clocks[ANIMATIONCLOCK].restart().asSeconds();
        for(int j = 0;j < m_dynamicObj.size();j++)
            m_dynamicObj[j]->updateAnimation();
    }
    if(time > 0.13){
        for(int i = 0;i < m_staticObj.size();i++){
            m_staticObj[i]->animation();
        }
    }
}

void GameController::gameOverOrDone(std::string msg[2]) {
    sf::RectangleShape fadedBackground;
    fadedBackground.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    fadedBackground.setFillColor(sf::Color(0, 0, 0, 90));

    m_window.draw(fadedBackground);

    gameTexts[0].setString(msg[0]);
    gameTexts[0].setOrigin(gameTexts[0].getGlobalBounds().width / 2, gameTexts[0].getGlobalBounds().height / 2);
    std::string spaces = "";
    for (int i = 0; i < (gameTexts[1].getString().getSize() - msg[1].size()) / 2; i++)
        spaces += ' ';
    gameTexts[1].setString(spaces + msg[1] + "\n\n" + gameTexts[1].getString());
    gameTexts[1].setOrigin(gameTexts[1].getGlobalBounds().width / 2, 0);

    for (int i = 0; i < 2; i++)
        m_window.draw(gameTexts[i]);
    m_window.display();
    paused = true;
    stats[isStopped] = 1;
    isGameOver = true;
}
