#include "../include/GameController.h"


GameController::GameController(sf::RenderWindow &window)
    : m_window(window), m_board(GameBoard()){
    ModifyBoard();
}

void GameController::run() {
    sf::Clock clock;
    print();
    while(m_window.isOpen())
    {
        if(auto event = sf::Event{}; m_window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    return;
            }
        }
        m_pacman->setDirection(keyHandler());
        const auto deltaTime = clock.restart();
        m_pacman->move(deltaTime.asSeconds());
        for(int i=0 ; i<m_ghosts.size() ; i++)
            m_ghosts[i]->move(deltaTime.asSeconds());

        handleCollision(*m_pacman);
        print();
    }
}

void GameController::print() {
    m_window.clear();
    m_board.draw(m_window);
    for(int obj = 0;obj < m_staticObj.size();obj++){
        m_staticObj[obj]->draw(&m_window);
    }
    m_pacman->draw(&m_window);
    for(int obj = 0;obj < m_ghosts.size();obj++){
        m_ghosts[obj]->draw(&m_window);
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
            m_pacman = std::make_unique<Pacman>(ResourcesManager::instance().getObjectTexture(PACMAN),tile.getPosition(),tile.getGlobalBounds().width - 10);
            break;
        }
        case GHOST_S:{
            m_ghosts.push_back(std::make_unique<Ghost>(ResourcesManager::instance().getObjectTexture(GHOST),tile.getPosition(),tile.getGlobalBounds().width));
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

sf::Keyboard::Key GameController::keyHandler() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        m_window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        return sf::Keyboard::Left;

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        return sf::Keyboard::Right;

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        return sf::Keyboard::Down;

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        return sf::Keyboard::Up;
}

void GameController::handleCollision(GameObject& other) {

    if (other.checkCollision(*m_pacman))
        other.handleCollision(*m_pacman);

    for (int j = 0; j < m_ghosts.size(); ++j)
    {
        if (m_pacman->checkCollision(*m_ghosts[j]))
            m_pacman->handleCollision(*m_ghosts[j]);
    }

    for (int i = 0; i < m_staticObj.size(); ++i)
    {
        if (other.checkCollision(*m_staticObj[i]))
            m_staticObj[i]->handleCollision(other);
    }
}

