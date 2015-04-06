#include <EventManager.hpp>
#include <EventListener.hpp>
#include <Event.hpp>
#include <OS.hpp>

#include <algorithm>

EventManager::EventManager() {
    m_listeners.clear();    
}

void EventManager::AddListener(EventListener *l) {
    if(!l)
        return;
    if(std::find(m_listeners.begin(), m_listeners.end(), l)==m_listeners.end()) {
        m_listeners.push_back(l);
        OS::get()->Log("[EventManager]: Registered event listener\n");
    }
}

void EventManager::Emit(Event* evt) {
    if(!evt)
        return;
    for(auto i = m_listeners.begin();i!=m_listeners.end();i++) {
        EventListener *l = *i;
        if(l->GetMask()&evt->GetMask()) {
            l->HandleEvent(evt);
       }
    }
}


