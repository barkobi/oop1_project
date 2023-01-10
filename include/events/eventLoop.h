#pragma once

#include "Event.h"
#include <queue>

class EventLoop{
public:
    static EventLoop &instance();

    void addEvent(Event event,sf::Vector2f position);
    std::pair<Event,sf::Vector2f> popEvent();
    bool hasEvent();

private:
    EventLoop();
    std::queue<std::pair<Event,sf::Vector2f>> events;
};

