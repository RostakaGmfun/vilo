#include <Actor.hpp>
#include <OS.hpp>
#include <APIDef.hpp>
#include <LuaState.hpp>
#include <InputManager.hpp>

Actor::Actor(std::string luaSrcPath, std::string name, int evtMask):
      m_luaSrc(luaSrcPath), m_luaState(NULL), m_name(name),
        EventListener(evtMask) {
    
}

void Actor::Hello() {
    OS::get()->Log("Hello, my name is %s\n", m_name.c_str());
}

bool Actor::Init() {
    m_luaState = new LuaState(m_luaSrc);
    if(!m_luaState->Init()) {
        OS::get()->Log("[Actor \"%s\"] Could not initialise LuaState\n", m_name.c_str());
        return false;
    }
    if(!m_luaState->DoFile()) {
        OS::get()->Log("[Actor \"%s\"] Could not execute file: \"%s\"\n", 
                       m_name.c_str(), m_luaSrc.c_str());
        CleanupLua();
        return false;
    }
    return true;
}

int Actor::Run() {
    return 0;
}

void Actor::Terminate() {
    CleanupLua();
}

void Actor::HandleEvent(Event* evt) {
    if(!evt||!m_luaState)
        return;
    switch(evt->GetType()) {
    case EVT_KB:
        KeyboardEvent* kbEvt = static_cast<KeyboardEvent*>(evt);
        if(kbEvt->pressed) // keypress event 
        {}
    }
}

void Actor::CleanupLua() {
    if(m_luaState) {
        m_luaState->Cleanup();
    }
}
