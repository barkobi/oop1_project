#include "../include/GameController.h"

GameController::GameController(sf::RenderWindow &window)
    : m_window(window), m_board(GameBoard()),m_cookies_on_board(0),m_lives(3){
    modifyBoard();
}

void GameController::run(){
    print();
    while(m_window.isOpen() && !backToMenu){
        if(auto event = sf::Event{}; m_window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                return;

        float deltaTime = clocks[MOVECLOCK].restart().asSeconds();
        for(int i=0 ; i<m_dynamicObj.size() ; i++)
        {
            m_dynamicObj[i]->move(deltaTime, m_board.getBoardBounds());
        }

        handleCollision();
        handleEvent();
        handleAnimations();
        print();
    }
}

void GameController::handleEvent() {
    while(EventLoop::instance().hasEvent()){
        auto event = EventLoop::instance().popEvent();
        switch (event.getEventType()){
            case CollapseWithGhost:
                m_lives--;
                if(m_lives == 0)
                    EventLoop::instance().addEvent(Event(GameOver));
                resetLevel();
                break;
            case EatCookie:{
                ResourcesManager::instance().playSound(CHEW_SOUND);
                m_cookies_on_board--;
                if(m_cookies_on_board == 0)
                    EventLoop::instance().addEvent(Event(LevelEnd));
                break;
            }
            case GotGift:
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
        }
        m_points+=event.getPoints();
    }
}

void GameController::print() {
    m_window.clear();
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
        for(int col = 0;col < map[row].length();col++)
            if (map[row][col] != ' ')
                charHandler(map[row][col], row, col);
    }
}

void GameController::charHandler(char type,int row,int col) {
    auto tile = m_board.getTile(row,col);
    switch (type) {
        case PACMAN_S:{
            m_dynamicObj.push_back(std::make_unique<Pacman>(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width * 0.75));
            std::swap(m_dynamicObj.front(),m_dynamicObj.back());
            break;
        }
        case GHOST_S:{
            m_dynamicObj.push_back(std::make_unique<Ghost>(ResourcesManager::instance().getObjectTexture(GHOST),tile.getPosition(),tile.getGlobalBounds().width * 0.9));
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
            m_staticObj.push_back(std::make_unique<Gift>(ResourcesManager::instance().getObjectTexture(GIFT),tile.getPosition(),tile.getGlobalBounds().width * 0.8));
            break;
        }
        case COOKIE_S:{
            m_cookies_on_board++;
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
}

void GameController::handleAnimations() {
    auto time = clocks[ANIMATIONCLOCK].getElapsedTime().asSeconds();
    if(time > 0.15){
        clocks[ANIMATIONCLOCK].restart().asSeconds();
        for(int j = 0;j < m_dynamicObj.size();j++)
            m_dynamicObj[j]->updateAnimation();
    }
    if(time > 0.09)
    {
        for(int i = 0;i < m_staticObj.size();i++)
        {
            m_staticObj[i]->animation();
        }
    }
}
