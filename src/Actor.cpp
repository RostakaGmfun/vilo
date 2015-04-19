#include <Actor.hpp>
#include <OS.hpp>
#include <APIDef.hpp>
#include <LuaState.hpp>
#include <luabind/luabind.hpp>
#include <luabind/class.hpp>
using namespace luabind;

Actor::Actor(std::string luaSrcPath, std::string name):
      m_luaSrc(luaSrcPath), m_luaState(NULL), m_name(name),
        Task(std::string("ACTOR_TASK_"+name).c_str(), 0, TASK_REPEATED) {
    
}

bool Actor::Init() {
    m_luaState = new LuaState(m_luaSrc);
    /*open(m_luaState->GetState());
    module(m_luaState->GetState()) [
            def("Hello",&OS::Hello)
    ]*/;
    OS::get()->RegisterAPI(m_luaState);
 
    if(!m_luaState->Do()) {
        OS::get()->Log("[Actor \"%s\"] Could not execute file: \"%s\"\n", 
                       m_name.c_str(), m_luaSrc.c_str());
        CleanupLua();
        return false;
    }
    Argument ret = m_luaState->PCall(ACTOR_CREATE);
    if(ret.t==ARG_INT)
        if(!ret.intVal) {
            CleanupLua();
            return false;
        }
    return true;
}

int Actor::Run() {
    Argument ret = m_luaState->Call(ACTOR_UPDATE);
    if(ret.t==ARG_INT)
        return ret.intVal;
    return 0;
}

void Actor::Terminate() {
    if(!m_luaState)
        return;
    m_luaState->Call(ACTOR_DESTROY);
    CleanupLua();
}

void Actor::CleanupLua() {
    if(m_luaState) {
        m_luaState->Cleanup();
    }
}
