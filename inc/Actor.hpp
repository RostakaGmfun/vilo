#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <EventListener.hpp>

#include <string>

class LuaState;

class Actor: public EventListener {
public:
    Actor(std::string luaSrcPath, std::string name, int evtMask);
    virtual bool Init();
    virtual int Run();
    virtual void Terminate();
    

    virtual void HandleEvent(Event* evt);

    void CleanupLua();
protected:
    std::string m_luaSrc;
    LuaState* m_luaState;
    std::string m_name;
};

#endif //ACTOR_HPP
