#include "GameBoard.h"
#include "cmath"
GameBoard::GameBoard() : m_total_levels(0){
    load_levels_files();
    if(m_total_levels>0){
        m_level.load_level(m_current_level);
        createBoard();
    }
}

Level &GameBoard::getLevel() { return m_level; }

sf::RectangleShape GameBoard::getTile(int row, int col) const { return m_matrix[row][col]; }

bool GameBoard::restartGame() {
    m_current_level = 1;
    if(!m_level.load_level(m_current_level))
        return false;
    createBoard();
    return true;
}

bool GameBoard::loadNextLevel() {
    m_current_level++;
    if (!m_level.load_level(m_current_level))
        return false;
    createBoard();
    return true;
}

void GameBoard::draw(sf::RenderWindow &window) const {
    for(int row=0 ; row<m_level.getHeight() ; row++){
        for(int col=0 ; col<m_level.getWidth() ; col++){
            window.draw(m_matrix[row][col]);
        }
    }
}

void GameBoard::createBoard() {
    m_matrix.clear();
    float tileSize = (std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / ((m_level.getWidth() + m_level.getHeight()) / 2));
    if(m_level.getHeight() == m_level.getWidth())
        tileSize *= 0.8;
    float topLeftX = (WINDOW_WIDTH / 2) - ((tileSize * m_level.getWidth()) / 2);
    float topLeftY = (WINDOW_HEIGHT / 2) - ((tileSize * m_level.getHeight())/2);

    for(int row=0 ; row<m_level.getHeight() ; row++){
        auto line = std::vector<sf::RectangleShape>();
        for(int col=0 ; col<m_level.getWidth() ; col++){
            auto r = sf::RectangleShape();
            r.setSize(sf::Vector2f(tileSize , tileSize ));
            r.setOrigin(tileSize*0.5,tileSize*0.5);
            r.setPosition(float((col *tileSize + topLeftX)) + tileSize * 0.5, float((row*tileSize + topLeftY)) + tileSize * 0.5);
            r.setFillColor(sf::Color(65,74,76,235));
            line.push_back(r);
        }
        m_matrix.push_back(line);
    }

    m_bounds.topLeftX = m_matrix[0][0].getPosition().x;
    m_bounds.topLeftY = m_matrix[0][0].getPosition().y;
    auto bottomRightTile = m_matrix[m_level.getHeight()-1][m_level.getWidth()-1];
    m_bounds.BottomRightX = bottomRightTile.getPosition().x + tileSize;
    m_bounds.BottomRightY = bottomRightTile.getPosition().y + tileSize;
    m_bounds.tile = tileSize;
    m_bounds.speed = sqrt(pow(m_bounds.topLeftX - m_bounds.BottomRightX, 2) + pow(m_bounds.topLeftY - m_bounds.BottomRightY, 2));
    m_bounds.speed *= 0.0275;

}

void GameBoard::load_levels_files(){
    auto str = read_files("find . -name \"lvl_*.txt\"");
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    auto cutStr = strtok(cstr, "\n");
    while (cutStr != NULL) {
        m_total_levels++;
        cutStr = strtok(NULL, " \n\0");
    }
}

std::string GameBoard::read_files(std::string command) {
    char buffer[128];
    std::string result = "";

    // Open pipe to file
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "popen failed!";
        exit(EXIT_FAILURE);
    }
    // read till end of process:
    while (!feof(pipe)) {
        // use buffer to read and add to result
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

Bounds &GameBoard::getBoardBounds() {return m_bounds;}

bool GameBoard::checkFinishGame() {
    return m_total_levels == m_current_level;
}

std::vector<std::vector<sf::RectangleShape>> GameBoard::getMatrix() {
    return m_matrix;
}

void GameBoard::reloadCurrentLevel() {
    m_level.setMapToStartOfLevel();
}
