#include <InputManager.hpp>
#include <Window.hpp>
#include <OS.hpp>
#include <algorithm>

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
                if(m_kb_callback)
                    m_kb_callback(KeyboardEvent(ev.key.keysym.sym, true));
            }
        break;
        case SDL_KEYUP: {
            auto i = std::find(m_kbState.begin(), m_kbState.end(), ev.key.keysym.sym);
            if(i!=m_kbState.end()) {
                m_kbState.erase(i);
                if(m_kb_callback)
                    m_kb_callback(KeyboardEvent(ev.key.keysym.sym, false));
            }
        }
        break;
        case SDL_MOUSEMOTION:
            m_mouseX = ev.motion.x;
            m_mouseY = ev.motion.y;
        break;
        case SDL_MOUSEBUTTONDOWN:
            
        break;
        case SDL_MOUSEBUTTONUP:
            
        break;
        case SDL_MOUSEWHEEL:
            
        break;
        default:
        break;
    }
}

bool InputManager::KeyDown(SDL_Keycode k) {
    return std::find(m_kbState.begin(), m_kbState.end(), k)==m_kbState.end();
}
