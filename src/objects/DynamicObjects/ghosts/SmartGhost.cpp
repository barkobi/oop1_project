
#include "SmartGhost.h"


SmartGhost::SmartGhost(sf::Vector2f position, float scaleFactor)
        : Ghost(ResourcesManager::instance().getObjectTexture(SMARTGHOST), position, scaleFactor), m_lastDirection(Up) {}

void SmartGhost::move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes){

    for(int i=0 ; i<bfsRes.size() ; i++){
        for(int j=0 ; j<bfsRes[i].size() ; j++)
            std::cout << bfsRes[i][j] << "   ";
        std::cout << "\n";
    }

    float tileSize = (boardBounds.BottomRightX-boardBounds.topLeftX)/ ((bfsRes.size()+bfsRes[0].size())/2);
    sf::Vector2f topLeft(boardBounds.topLeftX,boardBounds.topLeftY);
    auto ghostLoc = getSprite().getPosition()-topLeft+ sf::Vector2f(1,1);
    sf::Vector2i myLocation((int)(ghostLoc.y/tileSize),(int)(ghostLoc.x/tileSize));

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

    moveGhost(deltaTime,boardBounds,m_lastDirection);
}
