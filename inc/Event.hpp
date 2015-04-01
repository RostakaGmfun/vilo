#ifndef EVENT_HPP
#define EVENT_HPP

enum EVT_TYPE {
    EVT_INPUT
};

class Event {
public:
    EVT_TYPE type;
};

#endif //EVENT_HPP
