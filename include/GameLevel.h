#include <filesystem>
#include <SFML/Graphics.hpp>


class GameLevel{
public:
    GameLevel();

    //getters / setters
    int getCols() const;
    int getRows() const;
    bool setOnBoard(int flag);
    bool load_level(std::ifstream &board_file);
//    void validateLevel();
private:
    int m_cols, m_rows;
    bool isOnBoard;


};