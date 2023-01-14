#include "GameController.h"

GameController::GameController(sf::RenderWindow &window)
    : m_window(window), m_board(GameBoard()){
    stats[Life] = 3;
    stats[Points] = 0;
    stats[Cookies] = 0;
    modifyBoard();
}

void GameController::run(){
    print();
    std::vector<std::vector<int>> bfsRes;
    while(m_window.isOpen() && !backToMenu){
        if(auto event = sf::Event{}; m_window.pollEvent(event))
            if(event.type == sf::Event::Closed) {
                return;
            }
        float deltaTime = clocks[MOVECLOCK].restart().asSeconds();
        bfsRes = Brain::calculateBFS(Brain::addObjectsToMap(m_dynamicObj[0]->getSprite().getPosition(), m_board.getLevel().getMap(), m_board.getTile(0,0).getGlobalBounds().height ,
                                                                 m_board.getTile(0,0).getPosition(),m_dynamicObj[0]->getSprite().getGlobalBounds().width));
        for(int i=0 ; i<m_dynamicObj.size() ; i++){
            if(i > 0 && freezed)
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
    if(freezed){
        if(clocks[GIFTCLOCK].getElapsedTime().asSeconds() > 5)
            freezed = false;
    }
    if(super)
        if(clocks[GIFTCLOCK].getElapsedTime().asSeconds() > 5)
            m_dynamicObj[0]->getSprite().setTexture(*ResourcesManager::instance().getObjectTexture(0));

    while(EventLoop::instance().hasEvent()){
        auto event = EventLoop::instance().popEvent();
        switch (event.getEventType()){
            case CollapseWithGhost:
            {
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
                m_dynamicObj[0]->getSprite().setTexture(*ResourcesManager::instance().getObjectTexture(SUPERPACMAN));
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
            case GameOver:
                printf("Game Over!\n");
                backToMenu = true;
                break;
            case LevelEnd:{
                nextLevel();
                break;
            }
            case GameDone:
                printf("Game Done!\n");
                backToMenu = true;
                break;
            case TimeOver:
                //EventLoop::instance().addEvent(Event(GameOver));
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
                if(map[row][col]!= WALL_S && map[row][col]!= DOOR_S)
                    m_board.getLevel().removeChar(row,col);
            }
        }
    }
}

void GameController::charHandler(char type,int row,int col){
    auto tile = m_board.getTile(row,col);
    switch (type) {
        case PACMAN_S:{
            m_dynamicObj.push_back(std::make_unique<Pacman>(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width * 0.7));
            std::swap(m_dynamicObj.front(),m_dynamicObj.back());
            break;
        }
        case GHOST_S:{
            static bool ghost = false;
            if(ghost)
                m_dynamicObj.push_back(std::make_unique<RandomGhost>(tile.getPosition(),tile.getGlobalBounds().width));
            else
                m_dynamicObj.push_back(std::make_unique<SmartGhost>(tile.getPosition(),tile.getGlobalBounds().width));
            ghost = !ghost;
            break;
        }
        case KEY_S:{
            m_staticObj.push_back(std::make_unique<Key>(ResourcesManager::instance().getObjectTexture(KEY),tile.getPosition(),tile.getGlobalBounds().width * 0.8));
            break;
        }
        case DOOR_S:{
            m_staticObj.push_back(std::make_unique<Door>(ResourcesManager::instance().getObjectTexture(DOOR),tile.getPosition(),tile.getGlobalBounds().width));
            break;
        }
        case WALL_S:{
            m_staticObj.push_back(std::make_unique<Wall>(ResourcesManager::instance().getObjectTexture(WALL),tile.getPosition(),tile.getGlobalBounds().width));
            break;
        }
        case GIFT_S:{
            static int gift = -1;
            int tmp;
            do{tmp = rand()%4;} while (tmp==gift);
            gift = tmp;
            gift = 1;
            switch (gift) {
                case 0:
                    m_staticObj.push_back(std::make_unique<TimeAddGift>(ResourcesManager::instance().getObjectTexture(GIFT),tile.getPosition(),tile.getGlobalBounds().width * 0.7));
                    break;
                case 1:
                    m_staticObj.push_back(std::make_unique<SuperPacGift>(ResourcesManager::instance().getObjectTexture(GIFT),tile.getPosition(),tile.getGlobalBounds().width * 0.7));
                    break;
                case 2:
                    m_staticObj.push_back(std::make_unique<GhostFreezeGift>(ResourcesManager::instance().getObjectTexture(GIFT),tile.getPosition(),tile.getGlobalBounds().width* 0.7));
                    break;
                case 3:
                    m_staticObj.push_back(std::make_unique<LifeIncGift>(ResourcesManager::instance().getObjectTexture(GIFT),tile.getPosition(),tile.getGlobalBounds().width* 0.7));
                    break;
            }
            break;
        }
        case COOKIE_S:{
            stats[Cookies]++;
            m_staticObj.push_back(std::make_unique<Cookie>(ResourcesManager::instance().getObjectTexture(COOKIE),tile.getPosition(),tile.getGlobalBounds().width * 0.5));
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
    m_board.loadNextLevel();
    modifyBoard();
    m_gameBar.resetClock();
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
    if(index != -1)
        m_staticObj[index]->deleteObject();
}

void GameController::resetLevel() {
    for(int i=0 ; i<m_dynamicObj.size() ; i++)
        m_dynamicObj[i]->goToInitialPosition();

//    m_gameBar.resetClock();
}

void GameController::handleAnimations() {
    auto time = clocks[ANIMATIONCLOCK].getElapsedTime().asSeconds();
    if(time > 0.15){
        clocks[ANIMATIONCLOCK].restart().asSeconds();
        for(int j = 0;j < m_dynamicObj.size();j++)
            m_dynamicObj[j]->updateAnimation();
    }
    if(time > 0.13)
    {
        for(int i = 0;i < m_staticObj.size();i++)
        {
            m_staticObj[i]->animation();
        }
    }
}