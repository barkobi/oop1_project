
#include "RandomGhost.h"


RandomGhost::RandomGhost(sf::Vector2f position, float scaleFactor,float tileSize)
        : Ghost(ResourcesManager::instance().getObjectTexture(RANDOMGHOST), position, scaleFactor,tileSize), m_lastDirection(Up) {}

/**
 * move the ghost randomly.
 * @param deltaTime how much time passed till last movement
 * @param boardBounds board bounds
 * @param bfsRes result of BFS, *ignore*
 */
void RandomGhost::move(float deltaTime, Bounds boardBounds,std::vector<std::vector<int>> bfsRes){
    static float timeToSwitchDirection = 0;
    timeToSwitchDirection+=deltaTime;
    // change movement direction every 0.4 seconds
    if(timeToSwitchDirection> 0.4){
        int tmp;
        // randomize new direction till get new one.
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
    // move the ghost.
    moveGhost(deltaTime, boardBounds,m_lastDirection);
}
