#pragma once

#include "Event.h"
#include <queue>

/**
 * singleton class of event queue thats saves the events.
 */
class EventLoop{
public:
    // functions
    static EventLoop &instance();

    void addEvent(Event event);
    Event popEvent();
    bool hasEvent();

private:
    // private c-tor
    EventLoop();
    // member
    std::queue<Event> events;
};

