#pragma once
#include <SFML/Graphics.hpp>
enum EventType_t{
    EatCookie,
    GameOver,
    GameDone,
    LevelEnd,
    CollapseWithGhost,
    GotSuperGift,
    GotLifeGift,
    GotGhostFreezeGift,
    GotTimeAddGift,
    GotKey,
    TimeOver
};

class Event{
public:
    Event(EventType_t type,int pointsToAdd = 0);
    int getPoints() const;
    EventType_t getEventType() const;
private:
    int m_pointsToAdd;
    EventType_t m_eventType;
};