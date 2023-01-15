#include "eventLoop.h"
#include "pacmanState.h"


EventLoop::EventLoop() {}

EventLoop &EventLoop::instance() {
    static EventLoop eventLoop;
    return eventLoop;
}

bool EventLoop::hasEvent() {return !events.empty();}

Event EventLoop::popEvent() {
    auto popRes = events.front();
    events.pop();
    return popRes;
}

void EventLoop::addEvent(Event event) {
    events.push(event);
}
