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
 * @return get the map.
 */
std::vector<std::string> Level::getMap() {return m_map;}

/**
 * load the next map from the file
 * @param board_file the file to load from
 * @return is the level loaded successfully
 */
bool Level::load_level(int current_level) {
    std::ifstream file;
//    std::string f_name = "lvl_" + std::to_string(current_level) + ".txt";
    file.open("lvl_" + std::to_string(current_level) + ".txt");
    if(!file.is_open())
        return false;
    m_map.clear();
    file >> m_height >> m_width;
    file.get();
    for(int row=0 ; row<m_height ; row++){
        std::string new_row;
        if(!std::getline(file, new_row)){
            return false;
        }
        if(new_row.length() != m_width){
            std::cerr << "Board file is not valid\n";
            exit(EXIT_FAILURE);
        }
        m_map.push_back(new_row);
        m_mapCopy.push_back(new_row);
        new_row.clear();
    }
    file.close();
    return validateLevel();
}

/**
 * validate the level.
 * valid level include:
 * 1 pacman
 * 0 super pacmans
 * at least 1 cookie
 * equal number of doors and keys
 */
bool Level::validateLevel(){
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
        return false;
    }
    return true;
}

void Level::removeChar(int row, int col) {
    m_map[row][col] = ' ';
}

void Level::setMapToStartOfLevel() {
    for(int i=0 ; i<m_height ; i++){
        m_map[i] = m_mapCopy[i];
    }
}
