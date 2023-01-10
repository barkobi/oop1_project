#include "eventLoop.h"

EventLoop::EventLoop() {}

EventLoop &EventLoop::instance() {
    static EventLoop eventLoop;
    return eventLoop;
}

bool EventLoop::hasEvent() {return !events.empty();}

std::pair<Event,sf::Vector2f> EventLoop::popEvent() {
    auto popRes = events.front();
    events.pop();
    return popRes;
}

void EventLoop::addEvent(Event event,sf::Vector2f position) {
    events.push(std::make_pair(event,position));
}