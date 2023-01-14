
#include "SmartGhost.h"

#include <cmath>
SmartGhost::SmartGhost(sf::Vector2f position, float scaleFactor)
        : Ghost(ResourcesManager::instance().getObjectTexture(SMARTGHOST), position, scaleFactor * 0.75), m_lastDirection(Up) {
    myLocation.x = 0;
    myLocation.y = 0;
    collisionClock.restart().asSeconds();
}

void SmartGhost::move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes) {

    if(randomClock.getElapsedTime().asSeconds() > 2)
        randomize = false;

    if(randomize)
    {
        m_timetoswitch += deltaTime;
        if(m_timetoswitch > 0.5){
            m_timetoswitch = 0;
            Direction_t randomDir = static_cast<Direction_t>(rand() % 4);
            m_lastDirection = randomDir;
        }
        moveGhost(deltaTime,m_lastDirection);
        return;
    }
    float tileSize = boardBounds.tile;
    sf::Vector2f topLeft(boardBounds.topLeftY, boardBounds.topLeftX);
    float ghostLoc_x = (getSprite().getPosition().x - topLeft.y) / tileSize;
    float ghostLoc_y = (getSprite().getPosition().y - topLeft.x) / tileSize;
    if (std::abs(ghostLoc_x - myLocation.x) > 1) {
        myLocation.x = std::round(ghostLoc_x);
        collisionClock.restart().asSeconds();
    }
    if (std::abs(ghostLoc_y - myLocation.y) > 1) {
        myLocation.y = std::round(ghostLoc_y);
        collisionClock.restart().asSeconds();
    }
    std::cout << "Collision Clock Time elapesed : " << collisionClock.getElapsedTime().asSeconds() << "\n";
    if (collisionClock.getElapsedTime().asSeconds() > 1) {
        m_timetoswitch = 0;
        randomize = true;
        randomClock.restart().asSeconds();
    }
    int minLocation = tileSize * tileSize;
    if (bfsRes[myLocation.y - 1][myLocation.x] < bfsRes[myLocation.y][myLocation.x] &&
        bfsRes[myLocation.y - 1][myLocation.x] < minLocation) {
        m_lastDirection = Up;
        minLocation = bfsRes[myLocation.y - 1][myLocation.x];
    }
    if (bfsRes[myLocation.y + 1][myLocation.x] < bfsRes[myLocation.y][myLocation.x] &&
        bfsRes[myLocation.y - 1][myLocation.x] < minLocation) {
        m_lastDirection = Down;
        minLocation = bfsRes[myLocation.y + 1][myLocation.x];
    }
    if (bfsRes[myLocation.y][myLocation.x + 1] < bfsRes[myLocation.y][myLocation.x] &&
        bfsRes[myLocation.y - 1][myLocation.x] < minLocation) {
        m_lastDirection = Right;
        minLocation = bfsRes[myLocation.y][myLocation.x + 1];
    }
    if (bfsRes[myLocation.y][myLocation.x - 1] < bfsRes[myLocation.y][myLocation.x] &&
        bfsRes[myLocation.y - 1][myLocation.x] < minLocation) {
        m_lastDirection = Left;
    }
    moveGhost(deltaTime,m_lastDirection);
}
