
#include "SmartGhost.h"

SmartGhost::SmartGhost(sf::Vector2f position, float scaleFactor)
        : Ghost(ResourcesManager::instance().getObjectTexture(SMARTGHOST), position, scaleFactor * 0.9){}

void SmartGhost::move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes){
    Direction_t direction;
    static sf::Vector2i myLocation(0,0);

    float tileSize = boardBounds.tile;
    sf::Vector2f topLeft(boardBounds.topLeftX,boardBounds.topLeftY);
    sf::Vector2f ghostLoc = getSprite().getPosition() - topLeft + sf::Vector2f(getSprite().getGlobalBounds().width/2,getSprite().getGlobalBounds().height/2);
    ghostLoc.x/=boardBounds.tile;
    ghostLoc.y/=boardBounds.tile;
//    float ghostLoc_x = (getSprite().getPosition().x - topLeft.y) / tileSize;
//    float ghostLoc_y = (getSprite().getPosition().y - topLeft.x) / tileSize;

    if(std::abs(ghostLoc.x - myLocation.x) > 1 || std::abs(ghostLoc.y - myLocation.y) > 1){
        myLocation.x = std::round(ghostLoc.x);
        myLocation.y = std::round(ghostLoc.y);
    }
    int minLocation = tileSize * tileSize;
    if(bfsRes[myLocation.y - 1][myLocation.x] < bfsRes[myLocation.y][myLocation.x] && bfsRes[myLocation.y - 1][myLocation.x] < minLocation){
        direction = Up;
        minLocation = bfsRes[myLocation.y - 1][myLocation.x];
    }
    if(bfsRes[myLocation.y + 1][myLocation.x] < bfsRes[myLocation.y][myLocation.x] && bfsRes[myLocation.y - 1][myLocation.x] < minLocation){
        direction = Down;
        minLocation = bfsRes[myLocation.y + 1][myLocation.x];
    }
    if(bfsRes[myLocation.y][myLocation.x + 1] < bfsRes[myLocation.y][myLocation.x] && bfsRes[myLocation.y - 1][myLocation.x] < minLocation){
        direction = Right;
        minLocation = bfsRes[myLocation.y][myLocation.x + 1];
    }
    if(bfsRes[myLocation.y][myLocation.x - 1] < bfsRes[myLocation.y][myLocation.x] && bfsRes[myLocation.y - 1][myLocation.x] < minLocation){
        direction = Left;
    }
    moveGhost(deltaTime,boardBounds,direction);
}
