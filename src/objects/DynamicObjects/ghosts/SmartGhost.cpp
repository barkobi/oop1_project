
#include "SmartGhost.h"

#include <cmath>
SmartGhost::SmartGhost(sf::Vector2f position, float scaleFactor)
        : Ghost(ResourcesManager::instance().getObjectTexture(SMARTGHOST), position, scaleFactor * 0.9), m_lastDirection(Up) {
        myLocation.x = 0;
        myLocation.y = 0;
}

void SmartGhost::move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes){
    float tileSize = boardBounds.tile;
    sf::Vector2f topLeft(boardBounds.topLeftY,boardBounds.topLeftX);
    //auto ghostLoc = getSprite().getPosition()-topLeft+ sf::Vector2f(1,1);
    float ghostLoc_x = (getSprite().getPosition().x - topLeft.y) / tileSize;
    float ghostLoc_y = (getSprite().getPosition().y - topLeft.x) / tileSize;
//    std::cout << ghostLoc_y << " " << ghostLoc_x << "\n";
    if(std::abs(ghostLoc_x - myLocation.x) > 1 || std::abs(ghostLoc_y - myLocation.y) > 1)
    {
        myLocation.x = std::round(ghostLoc_x);
        myLocation.y = std::round(ghostLoc_y);
    }
    int minLocation = tileSize * tileSize;
    if(bfsRes[myLocation.y - 1][myLocation.x] < bfsRes[myLocation.y][myLocation.x] && bfsRes[myLocation.y - 1][myLocation.x] < minLocation)
    {
        m_lastDirection = Up;
        minLocation = bfsRes[myLocation.y - 1][myLocation.x];
    }
    if(bfsRes[myLocation.y + 1][myLocation.x] < bfsRes[myLocation.y][myLocation.x] && bfsRes[myLocation.y - 1][myLocation.x] < minLocation)
    {
        m_lastDirection = Down;
        minLocation = bfsRes[myLocation.y + 1][myLocation.x];
    }
    if(bfsRes[myLocation.y][myLocation.x + 1] < bfsRes[myLocation.y][myLocation.x] && bfsRes[myLocation.y - 1][myLocation.x] < minLocation)
    {
        m_lastDirection = Right;
        minLocation = bfsRes[myLocation.y][myLocation.x + 1];
    }
    if(bfsRes[myLocation.y][myLocation.x - 1] < bfsRes[myLocation.y][myLocation.x] && bfsRes[myLocation.y - 1][myLocation.x] < minLocation)
    {
        m_lastDirection = Left;
    }
    /*
    if(myLocation.y+1 < bfsRes.size()
        && bfsRes[myLocation.y+1][myLocation.x] <= bfsRes[myLocation.y-1][myLocation.x]
        && bfsRes[myLocation.y+1][myLocation.x] <= bfsRes[myLocation.y][myLocation.x+1]
        && bfsRes[myLocation.y+1][myLocation.x] <= bfsRes[myLocation.y][myLocation.x-1])
        m_lastDirection = Down;

    else if(myLocation.y-1 >=0
        && bfsRes[myLocation.y-1][myLocation.x] <= bfsRes[myLocation.y+1][myLocation.x]
        && bfsRes[myLocation.y-1][myLocation.x] <= bfsRes[myLocation.y][myLocation.x+1]
        && bfsRes[myLocation.y-1][myLocation.x] <= bfsRes[myLocation.y][myLocation.x-1])
        m_lastDirection = Up;

    else if(myLocation.x+1 < bfsRes[0].size()
        && bfsRes[myLocation.y][myLocation.x+1] <= bfsRes[myLocation.y+1][myLocation.x]
        && bfsRes[myLocation.y][myLocation.x+1] <= bfsRes[myLocation.y-1][myLocation.x]
        && bfsRes[myLocation.y][myLocation.x+1] <= bfsRes[myLocation.y][myLocation.x-1])
        m_lastDirection = Right;

    else if(myLocation.x-1>= 0
        && bfsRes[myLocation.y][myLocation.x-1] <= bfsRes[myLocation.y+1][myLocation.x]
        && bfsRes[myLocation.y][myLocation.x-1] <= bfsRes[myLocation.y-1][myLocation.x]
        && bfsRes[myLocation.y][myLocation.x-1] <= bfsRes[myLocation.y][myLocation.x+1])
        m_lastDirection = Left;
*/

    moveGhost(deltaTime,boardBounds,m_lastDirection);
}
