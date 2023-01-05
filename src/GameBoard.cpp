#include "GameBoard.h"

GameBoard::GameBoard() {
    m_board_file.open("Board.txt");
    if (!m_board_file.is_open()){
        std::cerr << "Cannot open Board.txt";
        exit(EXIT_FAILURE);
    }
    if (!m_level.load_level(&m_board_file)){
        std::cerr << "Cannot read from Board.txt";
        exit(EXIT_FAILURE);
    }
    createBoard();
}

GameBoard::~GameBoard() {
    m_board_file.close();
}

Level &GameBoard::getLevel() { return m_level; }

sf::RectangleShape GameBoard::getTile(int row, int col) const { return m_matrix[row][col]; }

void GameBoard::restartGame() {
    m_board_file.clear();
    m_board_file.seekg(0, std::ios::beg);
    if (!m_level.load_level(&m_board_file)){
        std::cerr << "Cannot read from Board.txt";
        exit(EXIT_FAILURE);
    }
    createBoard();
}

void GameBoard::loadNextLevel() {
    m_board_file.get();
    if (!m_level.load_level(&m_board_file)){
        std::cerr << "Cannot read from Board.txt";
        exit(EXIT_FAILURE);
    }
    createBoard();
}

void GameBoard::draw(sf::RenderWindow *window) const {
    for(int row=0 ; row<m_level.getHeight() ; row++){
        for(int col=0 ; col<m_level.getWidth() ; col++){
            window->draw(m_matrix[row][col]);
        }
    }
}

void GameBoard::createBoard() {
    m_matrix.clear();
    float tileSize = (WINDOW_WIDTH / (std::max(m_level.getWidth(), m_level.getHeight()))) * 0.8;
    float topLeftX = (WINDOW_WIDTH / 2) - ((tileSize * m_level.getWidth()) / 2);
    float topLeftY = (WINDOW_HEIGHT / 2) - ((tileSize * m_level.getHeight())/2);

    for(int row=0 ; row<m_level.getHeight() ; row++){
        auto line = std::vector<sf::RectangleShape>();
        for(int col=0 ; col<m_level.getWidth() ; col++){
            auto r = sf::RectangleShape();
            r.setSize(sf::Vector2f(tileSize , tileSize ));
            r.setPosition(float(col *tileSize + topLeftX), float(row*tileSize + topLeftY));
            r.setFillColor(sf::Color(100, 190, 190));
            line.push_back(r);
        }
        m_matrix.push_back(line);
    }
}