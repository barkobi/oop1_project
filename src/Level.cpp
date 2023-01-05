#include "level.h"

Level::Level() = default;

/**
 * @return get map width
 */
int Level::getWidth() const { return m_width;}

/**
 * @return get map height
 */
int Level::getHeight() const{return m_height;}

/**
 * get specific row from the map
 * @param row the row to get
 * @return
 */
std::string Level::getMapRow(int row) const {return m_map[row];}
/**
 * @return get the map.
 */
std::vector<std::string> Level::getMap() const {return m_map;}

/**
 * load the next map from the file
 * @param board_file the file to load from
 * @return is the level loaded successfully
 */
bool Level::load_level(std::ifstream *board_file) {
    m_map.clear();
    *board_file >> m_height >> m_width;
    (*board_file).get();
    for(int row=0 ; row<m_height ; row++){
        std::string new_row;
        if(!std::getline(*board_file, new_row)){
            return false;
        }
        if(new_row.length() != m_width){
            std::cerr << "Board file is not valid\n";
            exit(EXIT_FAILURE);
        }
        m_map.push_back(new_row);
        new_row.clear();
    }
    validateLevel();
    return true;
}

/**
 * validate the level.
 * valid level include:
 * 1 pacman
 * 0 super pacmans
 * at least 1 cookie
 * equal number of doors and keys
 */
void Level::validateLevel(){
    int cookies=0, doors=0, keys=0 ,pacman = 0, super_pm = 0;

    for(int row=0 ; row<m_height ; row++){
        for(int col=0 ; col<m_width ; col++){
            switch (m_map[row][col]) {
                case PACMAN_S:
                    pacman++;
                    break;
                case SUPER_PM_S:
                    super_pm++;
                    break;
                case DOOR_S:
                    doors++;
                    break;
                case KEY_S:
                    keys++;
                    break;
                case COOKIE_S:
                    cookies++;
                    break;
            }
        }
    }
    if (cookies < 1 || (doors != keys) || (super_pm != 0) || (pacman != 1) ){
        std::cerr << "Board file is not valid\n";
        exit(EXIT_FAILURE);
    }
}

/**
 * remove char from the map, insert space in the location
 * @param location the location of the char to remove
 */
void Level::removeChar(int row, int col) {
        m_map[row][col] = ' ';
}

/**
 * get the char in location
 * @param location the location to look at
 * @return the founded char
 */
char Level::getChar(int row, int col) const{
    return m_map[row][col];
}