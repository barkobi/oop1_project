#include "../include/GameController.h"


GameController::GameController(sf::RenderWindow &window) : m_window(&window),m_board(GameBoard()){
}

void GameController::run() {
    print();
    while(m_window->isOpen())
    {
        if (auto event = sf::Event{}; m_window->pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    m_window->close();
                    break;
            }
        }
        print();
    }
}

void GameController::print() {
    m_window->clear();
    for(int i = 0;i < m_board.getLevel().getHeight();i++)
    {
        for(int j =0;j < m_board.getLevel().getWidth();j++)
        {
            m_window->draw(m_board.getTile(i,j));
        }
    }
    m_board.draw(m_window);
    m_window->display();
}
