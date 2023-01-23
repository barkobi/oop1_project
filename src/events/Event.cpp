#include "Event.h"

/**
 * create new event
 * @param type event type (enum)
 * @param pointsToAdd how much points the event worth
 */
Event::Event(EventType_t type, int pointsToAdd)
    : m_eventType(type), m_pointsToAdd(pointsToAdd){}

int Event::getPoints() const { return m_pointsToAdd; }

EventType_t Event::getEventType() const {return m_eventType;}
