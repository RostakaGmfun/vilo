#ifndef EVENT_LISTENER_HPP
#define EVENT_LISTENER_HPP
class Event;

class EventListener {
public:
    HandleEvent(Event* evt);
};

#endif //EVENT_LISTENER_HPP
