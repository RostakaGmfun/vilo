#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP
#include <vector>

class Event;
class EventListener;

class EventManager {
public:
    static EventManager* get() {
        static EventManager instance;
        return &instance;
    }

    void AddListener(EventListener* listener);
    void Emit(Event* evt);
private:
    EventManager();

private:
    std::vector<EventListener*> m_listeners;
};

#endif //EVENT_MANAGER_HPP
