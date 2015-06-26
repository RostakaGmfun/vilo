#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <EventListener.hpp>

#include <string>

class LuaState;
class Scene;
struct lua_State;

class Actor: public EventListener {
public:
    Actor(LuaState* state, std::string name, int evtMask, Scene* p=nullptr);
    virtual bool Init();
    virtual void Update(float dt);
    virtual void Destroy();
    void Hello();    

    virtual void HandleEvent(Event* evt);

protected:
    lua_State* GetTable();
protected:
    std::string m_name;
    LuaState* m_state;
    Scene* m_parentScene;
};

#endif //ACTOR_HPP
