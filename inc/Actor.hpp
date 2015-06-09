#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <EventListener.hpp>

#include <string>

class LuaState;

class Actor: public EventListener {
public:
    Actor(LuaState* state, std::string name, int evtMask);
    virtual bool Init();
    virtual void Update(float dt);
    virtual void Terminate();
    void Hello();    

    virtual void HandleEvent(Event* evt);
protected:
    std::string m_name;
    LuaState* m_state;
};

#endif //ACTOR_HPP
