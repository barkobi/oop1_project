#pragma once

#include "Event.h"
#include <queue>

class EventLoop{
public:
    static EventLoop &instance();

    void addEvent(Event event);
    Event popEvent();
    bool hasEvent();

private:
    EventLoop();
    std::queue<Event> events;
};

