#ifndef EVENT_HPP
#define EVENT_HPP

enum EVT_TYPE {
    EVT_INPUT = 1<<0,
    EVT_NONE = 1<<1 //just for testing
};

class Event {
public:
    Event(int mask): m_mask(mask) {}
    int GetMask() const { return m_mask; }

protected:
    int m_mask;
};

#endif //EVENT_HPP
