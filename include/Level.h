#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "../values/symbols.h"
#include "fstream"

class Level {
public:
    // constructor
    Level();

    //getters / setters
    int getWidth() const;
    int getHeight() const;
    std::vector<std::string> getMap();

    // functions:
    bool load_level(int current_level);
    bool validateLevel();
    void removeChar(int row, int col);
    void setMapToStartOfLevel();

private:
    // members
    int m_width = 0, m_height = 0;
    std::vector<std::string> m_map;
    std::vector<std::string> m_mapCopy;

};