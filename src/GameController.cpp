#include "../include/GameController.h"


GameController::GameController(sf::RenderWindow &window)
    : m_window(window), m_board(GameBoard()){
    ModifyBoard();
}

void GameController::run() {
    print();
    while(m_window.isOpen())
    {
        if(auto event = sf::Event{}; m_window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    return;
            }
        }
        for(int i=0 ; i<m_dynamicObj.size() ; i++)
            m_dynamicObj[i]->move();
        print();
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
            m_dynamicObj.push_back(std::make_unique<Pacman>(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width));
            break;
        }
        case GHOST_S:{
            m_dynamicObj.push_back(std::make_unique<Ghost>(ResourcesManager::instance().getObjectTexture(GHOST),tile.getPosition(),tile.getGlobalBounds().width));
            break;
        }
        case KEY_S:{
            m_staticObj.push_back(std::make_unique<Key>(ResourcesManager::instance().getObjectTexture(KEY),tile.getPosition(),tile.getGlobalBounds().width));
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
            m_staticObj.push_back(std::make_unique<Gift>(ResourcesManager::instance().getObjectTexture(GIFT),tile.getPosition(),tile.getGlobalBounds().width));
            break;
        }
        case COOKIE_S:{
            m_staticObj.push_back(std::make_unique<Cookie>(ResourcesManager::instance().getObjectTexture(COOKIE),tile.getPosition(),tile.getGlobalBounds().width));
            break;
        }
    }
}
