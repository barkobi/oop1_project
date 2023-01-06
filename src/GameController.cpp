#include "../include/GameController.h"


GameController::GameController(sf::RenderWindow &window)
    : m_window(window), m_board(GameBoard()){}

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
    for(int row=0 ; row<m_board.getLevel().getHeight() ; row++){
        for(int col=0 ; col<m_board.getLevel().getWidth() ; col++){
            m_window.draw(m_board.getTile(row,col));
        }
    }
    m_board.draw(m_window);
    m_window.display();
}
