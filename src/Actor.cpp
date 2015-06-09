#include <Actor.hpp>
#include <OS.hpp>
#include <APIDef.hpp>
#include <InputManager.hpp>
#include <LuaState.hpp>

Actor::Actor(LuaState* state, std::string name, int evtMask):
        EventListener(evtMask), m_name(name), m_state(state)
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

