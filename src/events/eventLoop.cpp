#include "eventLoop.h"
#include "pacmanState.h"


EventLoop::EventLoop() {}

/**
 * get event loop instance, singleton.
 * @return event loop instance
 */
EventLoop &EventLoop::instance() {
    static EventLoop eventLoop;
    return eventLoop;
}

/**
 * check if there is unhandled even in the queue.
 */
bool EventLoop::hasEvent() {return !events.empty();}

/**
 * get the first event to handle from the queue.
 * @return event
 */
Event EventLoop::popEvent() {
    auto popRes = events.front();
    events.pop();
    return popRes;
}

/**
 * add new event to the queue.
 * @param event the event to add.
 */
void EventLoop::addEvent(Event event) {
    events.push(event);
}
