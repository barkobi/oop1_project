
#include "RandomGhost.h"


RandomGhost::RandomGhost(sf::Vector2f position, float scaleFactor)
        : Ghost(ResourcesManager::instance().getObjectTexture(RANDOMGHOST), position, scaleFactor), m_lastDirection(Up) {}

void RandomGhost::move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes){
    static float timeToSwitchDirection = 0;
    timeToSwitchDirection+=deltaTime;
    if(timeToSwitchDirection> 0.7){
        int tmp;
        do{tmp =rand() % 4;}while(tmp ==m_lastDirection);

        switch (tmp){
            case 0:
                m_lastDirection = Right;
                break;
            case 1:
                m_lastDirection = Left;
                break;
            case 2:
                m_lastDirection = Up;
                break;
            case 3:
                m_lastDirection = Down;
                break;
        }
        timeToSwitchDirection = 0;
    }
    moveGhost(deltaTime,m_lastDirection);
}
