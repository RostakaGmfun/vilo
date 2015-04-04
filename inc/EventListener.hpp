#ifndef EVENT_LISTENER_HPP
#define EVENT_LISTENER_HPP
#include <Event.hpp>

class EventListener {
public:
    EventListener(int mask): m_mask(mask) {}
    virtual void HandleEvent(Event* evt) = 0;
    int GetMask() const { return m_mask; }

protected:
    int m_mask;
};

#endif //EVENT_LISTENER_HPP
