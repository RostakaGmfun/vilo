#include <Window.hpp>
#include <OS.hpp>
#include <string>
#include <ConfigSystem.hpp>
#include <ConfigVars.hpp>
#include <InputManager.hpp>
#include <FSManager.hpp>
#include <EventManager.hpp>

Window::Window(): m_window(NULL) {

}

bool Window::Init() {
    ReadConfig();
    if(m_window) return true;
    if(SDL_Init(SDL_INIT_VIDEO) <0) {
        OS::get()->Log("Window::Init(): error initialising SDL\n");
        return false;
    }
    Uint32 flags = SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL;
    if(m_fullscreen)
        flags|=SDL_WINDOW_FULLSCREEN;
    m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                m_width, m_height, flags);
    return true;
}

void Window::ReadConfig() {
    //TODO add config.lua existance check
    std::string title = ConfigSystem::get()->GetString(WIN_TITLE);
    m_title = new char[title.size()+1];
    std::copy(title.begin(), title.end(), m_title);
    m_title[title.size()] = '\0';
    m_width = ConfigSystem::get()->GetInt(WIN_WIDTH);
    if(m_width<=0)
        m_width = 640;
    m_height = ConfigSystem::get()->GetInt(WIN_HEIGHT);
    if(m_height<=0)
        m_height = 480;
    m_fullscreen = ConfigSystem::get()->GetInt(WIN_FULLSCREEN);
}

int Window::EventLoop() {
    if(!m_window) return 0;
    m_quit = 1;
    SDL_Event e;

        while(SDL_PollEvent(&e)!=0) {
            switch(e.type) {
            case SDL_QUIT:
                m_quit = 0;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEWHEEL:
                InputManager::get()->ProcessEvent(e);
                break;
            case SDL_WINDOWEVENT:
                switch(e.window.type) {
                    case SDL_WINDOWEVENT_RESIZED:
                        EventManager::get()->Emit(
                            new ResizeEvent(e.window.data1, e.window.data2));
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
            }
        }
    // Quit();
    return m_quit;
}

void Window::Quit() {
    m_quit = 0;
    SDL_Quit();
}
