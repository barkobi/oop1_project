#include "Event.h"

Event::Event(EventType_t type, int pointsToAdd)
    : m_eventType(type), m_pointsToAdd(pointsToAdd){}

int Event::getPoints() const { return m_pointsToAdd; }

EventType_t Event::getEventType() const {return m_eventType;}
