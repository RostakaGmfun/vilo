#include <InputManager.hpp>
#include <Window.hpp>
#include <OS.hpp>
#include <EventManager.hpp>
//hope code is readable guyz :D
#include <algorithm>
#include <map>

bool InputManager::Init(Window* win) {
    m_client = win;
    if(!m_client) {
        OS::get()->Log("[InputManager::Init()]: NULL client window specified\n");
        return false;
    }

}

void InputManager::ProcessEvent(SDL_Event ev) {
    switch(ev.type) {
        case SDL_KEYDOWN:
            if(std::find(m_kbState.begin(), m_kbState.end(), ev.key.keysym.sym)==m_kbState.end()) {
                m_kbState.push_back(ev.key.keysym.sym);
                KeyboardEvent *event = new KeyboardEvent(ev.key.keysym.sym, true);
                if(m_kb_callback)
                    m_kb_callback(event);
                EventManager::get()->Emit(event);
            }
        break;
        case SDL_KEYUP: {
            auto i = std::find(m_kbState.begin(), m_kbState.end(), ev.key.keysym.sym);
            if(i!=m_kbState.end()) {
                m_kbState.erase(i);
                KeyboardEvent *event = new KeyboardEvent(ev.key.keysym.sym, false);
                if(m_kb_callback)
                    m_kb_callback(event);
                EventManager::get()->Emit(event);
            }
        }
        break;
        case SDL_MOUSEMOTION:
            m_mouseX = ev.motion.x;
            m_mouseY = ev.motion.y;
        break;
        case SDL_MOUSEBUTTONDOWN: {
            int press = -1;
            if(ev.button.button==SDL_BUTTON_LEFT) {
                m_mouseState[0] = true;
                press = 0;
            }
            
            if(ev.button.button==SDL_BUTTON_MIDDLE) {
                m_mouseState[1] = true;
                press = 1;
            }
            if(ev.button.button==SDL_BUTTON_RIGHT) {
                m_mouseState[2] = true;
                press = 2;
            }
            MouseEvent *event = new MouseEvent(ev.button.x, ev.button.y, press, true);
            if(m_mouse_callback)
                m_mouse_callback(event);
            EventManager::get()->Emit(event);
        break;
        }
        case SDL_MOUSEBUTTONUP: {
            int press = -1;
            if(ev.button.button==SDL_BUTTON_LEFT) {
                m_mouseState[0] = true;
                press = 0;
            }
            
            if(ev.button.button==SDL_BUTTON_MIDDLE) {
                m_mouseState[1] = true;
                press = 1;
            }
            if(ev.button.button==SDL_BUTTON_RIGHT) {
                m_mouseState[2] = true;
                press = 2;
            }
            MouseEvent *event = new MouseEvent(ev.button.x, ev.button.y, press, false);
            if(m_mouse_callback)
                m_mouse_callback(event);
            EventManager::get()->Emit(event);
        break;
        }
        break;
        case SDL_MOUSEWHEEL:
         //TODO   
        break;
        default:
        break;
    }
}

bool InputManager::KeyDown(SDL_Keycode k) {
    return std::find(m_kbState.begin(), m_kbState.end(), k)==m_kbState.end();
}

std::string InputManager::ToLuaKey(KeyboardEvent* evt) {
    static std::map<SDL_Keycode,std::string> sdl_to_lua;
}
