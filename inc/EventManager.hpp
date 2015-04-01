#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP
class Event;

class EventManager {
public:
    static EventManager* get() {
        static EventManager instance;
        return &instance;
    }

    void Emit(Event* evt);
private:
    EvenManager() {}
};

#endif //EVENT_MANAGER_HPP
