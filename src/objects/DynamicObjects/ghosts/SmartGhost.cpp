
#include "SmartGhost.h"

#include <cmath>
SmartGhost::SmartGhost(sf::Vector2f position, float scaleFactor,float tileSize)
        : Ghost(ResourcesManager::instance().getObjectTexture(SMARTGHOST), position, scaleFactor,tileSize), m_myLocation(1,1) {
    m_collisionClock.restart().asSeconds();
}

/**
 * move the ghost according to BFS result.
 * @param deltaTime how much time passed till last movement
 * @param boardBounds board bounds
 * @param bfsRes result of BFS.
 */
void SmartGhost::move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes) {
    // update my tile.
    calcMyLocation(boardBounds);

    // save all available direction from the bfs tree.
    int right = m_myLocation.x+1 < bfsRes[0].size() ? bfsRes[m_myLocation.y][m_myLocation.x+1] : WINDOW_WIDTH;
    int left = m_myLocation.x-1 >=0 ? bfsRes[m_myLocation.y][m_myLocation.x-1] : WINDOW_WIDTH;
    int up = m_myLocation.y-1>=0 ? bfsRes[m_myLocation.y-1][m_myLocation.x] : WINDOW_WIDTH;
    int down = m_myLocation.y+1 < bfsRes.size() ? bfsRes[m_myLocation.y+1][m_myLocation.x] : WINDOW_WIDTH;

    // pair the distance with the direction to keep the direction after sorting.
    std::pair<int, Direction_t> dirs[4] = {std::make_pair(right,Right),
                                           std::make_pair(left, Left),
                                           std::make_pair(up,Up),
                                           std::make_pair(down,Down)};

    // sort by distance.
    for(int round=0; round < 4-1;round++){
        for(int place=0; place< 4-round-1; place++)
            if(dirs[place].first >= dirs[place + 1].first){
                std::swap(dirs[place],dirs[place + 1]);
            }
    }
    // check if blocked in same position more than 0.7 seconds.
    if (m_collisionClock.getElapsedTime().asSeconds() > 0.7)
        m_blocked = true;

    // if not blocked move in the fastest way, if blocked move in
    // the second - fastest way.
    moveGhost(deltaTime,boardBounds, dirs[m_blocked].second);
}

/**
 * calculate my location in the board
 * @param boardBounds board bounds.
 */
void SmartGhost::calcMyLocation(Bounds boardBounds) {
    // calculate in what tile the ghost is
    float tileSize = boardBounds.tile;
    sf::Vector2f topLeft(boardBounds.topLeftX, boardBounds.topLeftY);
    float ghostLoc_x = (getSprite().getPosition().x - topLeft.x) / tileSize;
    float ghostLoc_y = (getSprite().getPosition().y - topLeft.y) / tileSize;

    // check if changed tile:
    // if change set block to false,save the location and resent the blocked clock.
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