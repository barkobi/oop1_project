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
        m_objects[obj];
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
        for(int col = 0;col < map[row].length();col++)
            if(map[row][col] != ' ')
            {
                if(map[row][col] == 'a')
                {
                    auto tile = m_board.getTile(row,col);
                    m_objects.push_back(std::make_unique<Pacman>(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width));
                    std::cout << (m_objects[0].get());
                }
//                auto gameObjectPtr = charHanlder(map[row][col],row,col);
            }
    }
}

std::unique_ptr<GameObject> GameController::charHanlder(char type,int row,int col) {
    std::unique_ptr<GameObject> retVal;
    std::unique_ptr<Pacman> temp;
    auto tile = m_board.getTile(row,col);
    switch (type) {
        case PACMAN_S:{
            auto obj = Pacman(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width);
            break;
        }
        case GHOST_S:{
            auto obj = Ghost(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width);
            retVal = std::make_unique<Ghost>(obj);
            break;
        }
        case KEY_S:{
            auto obj = Key(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width);
            retVal = std::make_unique<Key>(obj);
            break;
        }
        case DOOR_S:{
            auto obj = Door(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width);
            retVal = std::make_unique<Door>(obj);
            break;
        }
        case WALL_S:{
            auto obj = Wall(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width);
            retVal = std::make_unique<Wall>(obj);
            break;
        }
        case GIFT_S:{
            auto obj = Gift(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width);
            retVal = std::make_unique<Gift>(obj);
            break;
        }
        case COOKIE_S:{
            auto obj = Cookie(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width);
            retVal = std::make_unique<Cookie>(obj);
            break;
        }
    }
    return temp;
}
