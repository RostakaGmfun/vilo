#include <Actor.hpp>
#include <OS.hpp>
#include <APIDef.hpp>
#include <InputManager.hpp>
#include <LuaState.hpp>
#include <Game.hpp>
#include <Scene.hpp>

Actor::Actor(LuaState* state, std::string name, int evtMask, Scene* p):
        EventListener(evtMask), m_name(name), m_state(state), m_parentScene(p)
{}

void Actor::Hello() {
    OS::get()->Log("Hello, my name is %s\n", m_name.c_str());
}

bool Actor::Init() {
    if(!m_state)
        return false;
    return true;
}

void Actor::Update(float dt) {
    v_ASSERT(m_state);
    lua_State* L = m_state->GetState();
    lua_pushlightuserdata(L, (void*)this);
    lua_gettable(L, LUA_REGISTRYINDEX);
    v_ASSERT(lua_istable(L, -1));
    lua_getfield(L, -1, "update");
    lua_pushnumber(L, dt);
    lua_call(L, 1, 0);
}

void Actor::Terminate() {
}

void Actor::HandleEvent(Event* evt) {
    switch(evt->GetType()) {
    case EVT_KB: {
        KeyboardEvent* kbEvt = static_cast<KeyboardEvent*>(evt);
        if(kbEvt->pressed) { // keypress event
            
        }

    }
    default: 
        break;
    }
}

