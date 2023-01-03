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
                    return;

            }
        }
        print();
    }
}

void GameController::print() {
    m_window->clear();
    for(int i = 0;i < m_board.getRows();i++)
    {
        for(int j =0;j < m_board.getCols();j++)
        {
            m_window->draw(m_board.getTile(i,j));
        }
    }
    m_window->display();
}
