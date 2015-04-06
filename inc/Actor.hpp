#ifndef ACTOR_HPP
#define ACTOR_HPP
#include <Task.hpp>

#include <string>

class LuaState;

class Actor: public Task {
public:
    Actor(std::string luaSrcPath, std::string name);
    virtual bool Init();
    virtual int Run();
    virtual void Terminate();
    
    void CleanupLua();
protected:
    std::string m_luaSrc;
    LuaState* m_luaState;
    std::string m_name;
};

#endif //ACTOR_HPP
