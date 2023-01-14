
#include "SmartGhost.h"

SmartGhost::SmartGhost(sf::Vector2f position, float scaleFactor)
        : Ghost(ResourcesManager::instance().getObjectTexture(SMARTGHOST), position, scaleFactor * 0.9){}

void SmartGhost::move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes, std::vector<std::vector<sf::RectangleShape>> matrix){
    static Direction_t direction;
    static sf::Vector2i myLocation(0,0);

    sf::Vector2f topLeft(boardBounds.topLeftX,boardBounds.topLeftY);
    sf::Vector2f ghostLoc = getSprite().getPosition() - topLeft + sf::Vector2f(getSprite().getGlobalBounds().width/2,getSprite().getGlobalBounds().height/2);
    ghostLoc.x/=boardBounds.tile;
    ghostLoc.y/=boardBounds.tile;

    if(std::abs(ghostLoc.x - myLocation.x) > 1 || std::abs(ghostLoc.y - myLocation.y) > 1){
        myLocation.x = std::round(ghostLoc.x);
        myLocation.y = std::round(ghostLoc.y);
    }
//    bool containTopLeft = matrix[myLocation.y][myLocation.x].getGlobalBounds().contains(getSprite().getPosition());
//    bool containBottomRight = !matrix[myLocation.y][myLocation.x].getGlobalBounds().contains(getSprite().getPosition()+sf::Vector2f(getSprite().getGlobalBounds().width,getSprite().getGlobalBounds().height));
//    std::cout << direction << std::endl;
//    if(!containBottomRight && !containTopLeft){
//        moveGhost(deltaTime,direction);
//        return;
//    }

    int minLocation = boardBounds.tile * boardBounds.tile;
    if(!(direction==Up && badMove) && myLocation.y-1 >= 0 && bfsRes[myLocation.y - 1][myLocation.x] < bfsRes[myLocation.y][myLocation.x] && bfsRes[myLocation.y - 1][myLocation.x] < minLocation){
        direction = Up;
        minLocation = bfsRes[myLocation.y - 1][myLocation.x];
    }
    if(!(direction==Down && badMove) && myLocation.y+1 < bfsRes.size() && bfsRes[myLocation.y + 1][myLocation.x] < bfsRes[myLocation.y][myLocation.x] && bfsRes[myLocation.y - 1][myLocation.x] < minLocation){
        direction = Down;
        minLocation = bfsRes[myLocation.y + 1][myLocation.x];
    }
    if(!(direction==Right && badMove) && myLocation.x+1 < bfsRes[0].size() && bfsRes[myLocation.y][myLocation.x + 1] < bfsRes[myLocation.y][myLocation.x] && bfsRes[myLocation.y - 1][myLocation.x] < minLocation){
        direction = Right;
        minLocation = bfsRes[myLocation.y][myLocation.x + 1];
    }
    if(!(direction==Left && badMove) && myLocation.x-1 >= 0 && bfsRes[myLocation.y][myLocation.x - 1] < bfsRes[myLocation.y][myLocation.x] && bfsRes[myLocation.y - 1][myLocation.x] < minLocation){
        direction = Left;
    }
    badMove = false;
    moveGhost(deltaTime,direction);
}
