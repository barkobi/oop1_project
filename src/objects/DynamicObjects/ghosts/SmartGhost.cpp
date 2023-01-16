
#include "SmartGhost.h"

#include <cmath>
SmartGhost::SmartGhost(sf::Vector2f position, float scaleFactor,float tileSize)
        : Ghost(ResourcesManager::instance().getObjectTexture(SMARTGHOST), position, scaleFactor,tileSize), m_myLocation(1,1) {
    m_collisionClock.restart().asSeconds();
}

void SmartGhost::move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes) {
    calcMyLocation(boardBounds);

    int right = m_myLocation.x+1 < bfsRes[0].size() ? bfsRes[m_myLocation.y][m_myLocation.x+1] : WINDOW_WIDTH;
    int left = m_myLocation.x-1 >=0 ? bfsRes[m_myLocation.y][m_myLocation.x-1] : WINDOW_WIDTH;
    int up = m_myLocation.y-1>=0 ? bfsRes[m_myLocation.y-1][m_myLocation.x] : WINDOW_WIDTH;
    int down = m_myLocation.y+1 < bfsRes.size() ? bfsRes[m_myLocation.y+1][m_myLocation.x] : WINDOW_WIDTH;

    std::pair<int, Direction_t> dirs[4] = {std::make_pair(right,Right),
                                           std::make_pair(left, Left),
                                           std::make_pair(up,Up),
                                           std::make_pair(down,Down)};

    for(int round=0; round < 4-1;round++){
        for(int place=0; place< 4-round-1; place++)
            if(dirs[place].first >= dirs[place + 1].first){
                std::swap(dirs[place],dirs[place + 1]);
            }
    }
    if (m_collisionClock.getElapsedTime().asSeconds() > 0.7)
        m_blocked = true;

    moveGhost(deltaTime,boardBounds, dirs[m_blocked].second);
}

void SmartGhost::calcMyLocation(Bounds boardBounds) {
    float tileSize = boardBounds.tile;
    sf::Vector2f topLeft(boardBounds.topLeftX, boardBounds.topLeftY);
    float ghostLoc_x = (getSprite().getPosition().x - topLeft.x) / tileSize;
    float ghostLoc_y = (getSprite().getPosition().y - topLeft.y) / tileSize;
    if (std::abs(ghostLoc_x - m_myLocation.x) > 1) {
        m_blocked = false;
        m_myLocation.x = std::round(ghostLoc_x);
        m_collisionClock.restart().asSeconds();
    }
    if (std::abs(ghostLoc_y - m_myLocation.y) > 1) {
        m_blocked = false;
        m_myLocation.y = std::round(ghostLoc_y);
        m_collisionClock.restart().asSeconds();
    }
}