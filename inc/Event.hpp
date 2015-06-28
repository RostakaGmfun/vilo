#ifndef EVENT_HPP
#define EVENT_HPP

enum EVT_MASK {
    EVT_INPUT = 1<<0,
    EVT_NONE = 1<<1,
    EVT_WINDOW = 1<<2
};

enum EVT_TYPE {
    // input events
    EVT_KB = 1,
    EVT_MOUSE,
    
    //window events
    EVT_RESIZE
};

class Event {
public:
    Event(int mask, EVT_TYPE t): m_mask(mask), m_type(t) {}
    int GetMask() const { return m_mask; }
    EVT_TYPE GetType() const { return m_type; }
    
protected:
    int m_mask;
    EVT_TYPE m_type;
};

#endif //EVENT_HPP
