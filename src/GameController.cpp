#include "../include/GameController.h"

GameController::GameController(sf::RenderWindow &window)
    : m_window(window), m_board(GameBoard()),m_cookies_on_board(0){
}

void GameController::run() {
    m_dynamicObj.clear();
    m_staticObj.clear();
    ModifyBoard();
    m_lives = 3;
    sf::Clock clock;
    sf::Clock pa;
    print();
    while(m_window.isOpen()){
        if(m_cookies_on_board == 0)
        {
            if(!m_board.checkFinishGame())
            {
                m_board.loadNextLevel();
                run();
            }
            else
            {
                std::cout << "GAME DONE";
                break;
            }
        }
        if(auto event = sf::Event{}; m_window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    return;
            }
        }
        float deltaTime = clock.restart().asSeconds();
        for(int i=0 ; i<m_dynamicObj.size() ; i++)
        {
            if(pa.getElapsedTime().asSeconds() > 0.15){
                m_dynamicObj[i]->updateAnimation();
                pa.restart();
            }
            m_dynamicObj[i]->move(deltaTime, m_board.getBoardBounds());
        }

        handleCollision();
        handleEvent();
        print();
    }
}

void GameController::handleEvent() {
    while(EventLoop::instance().hasEvent()){
        auto event = EventLoop::instance().popEvent();
        switch (event.getEventType()){
            case CollapseWithGhost:{
                m_lives--;
                break;
            }
            case EatCookie:{
                ResourcesManager::instance().playSound(CHEW_SOUND);
                m_cookies_on_board--;}
                break;
            case GotGift:
                break;
            case GotKey:
                break;
            case GameOver:
                break;
            case LevelEnd:
                break;
        }
        m_points+=event.getPoints();

        printf("points: %d" , m_points);
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

void GameController::ModifyBoard() {
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
            m_dynamicObj.push_back(std::make_unique<Pacman>(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width * 0.8));
            break;
        }
        case GHOST_S:{
            m_dynamicObj.push_back(std::make_unique<Ghost>(ResourcesManager::instance().getObjectTexture(GHOST),tile.getPosition(),tile.getGlobalBounds().width * 0.8));
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

