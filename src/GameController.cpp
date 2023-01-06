#include "../include/GameController.h"


GameController::GameController(sf::RenderWindow &window)
    : m_window(window), m_board(GameBoard()){
    ModifyBoard();
}

void GameController::run() {
    print();
    while(m_window.isOpen())
    {
        if (auto event = sf::Event{}; m_window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    return;
            }
        }
        print();
    }
}

void GameController::print() {
    m_window.clear();
    m_board.draw(m_window);
    for(int obj = 0;obj < m_objects.size();obj++){
        m_objects[obj]->draw(&m_window);
    }
    m_window.display();
}

void GameController::ModifyBoard() {

    float scaleFac = m_board.getTile(0,0).getGlobalBounds().width;
    scaleFac /= IMAGE_DIMENSIONS;
    auto map = m_board.getLevel().getMap();
    for(int row = 0;row < map.size();row++)
    {
        for(int col = 0;col < map[row].length();col++){
            if (map[row][col] == ' ')
                continue;
            m_objects.push_back(charHandler(map[row][col], row, col));
        }
    }
}

std::unique_ptr<GameObject> GameController::charHandler(char type,int row,int col) {
    auto tile = m_board.getTile(row,col);
    switch (type) {
        case PACMAN_S:{
            return std::make_unique<Pacman>(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width);
        }
        case GHOST_S:{
            return std::make_unique<Ghost>(ResourcesManager::instance().getObjectTexture(GHOST),tile.getPosition(),tile.getGlobalBounds().width);
        }
        case KEY_S:{
            return std::make_unique<Key>(ResourcesManager::instance().getObjectTexture(KEY),tile.getPosition(),tile.getGlobalBounds().width);
        }
        case DOOR_S:{
            return std::make_unique<Door>(ResourcesManager::instance().getObjectTexture(DOOR),tile.getPosition(),tile.getGlobalBounds().width);
        }
        case WALL_S:{
            return std::make_unique<Wall>(ResourcesManager::instance().getObjectTexture(WALL),tile.getPosition(),tile.getGlobalBounds().width);
        }
        case GIFT_S:{
            return std::make_unique<Gift>(ResourcesManager::instance().getObjectTexture(GIFT),tile.getPosition(),tile.getGlobalBounds().width);
        }
        case COOKIE_S:{
            return std::make_unique<Cookie>(ResourcesManager::instance().getObjectTexture(COOKIE),tile.getPosition(),tile.getGlobalBounds().width);
        }
    }
}
