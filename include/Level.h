#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "../values/symbols.h"

class Level {
public:
    // constructor
    Level();

    //getters / setters
    int getWidth() const;
    int getHeight() const;
    std::string getMapRow(int row) const;
    std::vector<std::string> getMap() const;
    char getChar(int row, int col) const;

    // functions:
    bool load_level(std::ifstream *board_file);
    void validateLevel();
    void removeChar(int row, int col);

private:
    // members
    int m_width = 0, m_height = 0;
    std::vector<std::string> m_map;
};