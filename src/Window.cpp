#include <Window.hpp>
#include <OS.hpp>
#include <string>
#include <ConfigSystem.hpp>
#include <ConfigVars.hpp>

Window::Window(): m_window(NULL) {

}

bool Window::Init() {
    ReadConfig();
    if(m_window) return true;
    if(SDL_Init(SDL_INIT_VIDEO) <0) {
        OS::get()->Log("Window::Init(): error initialising SDL\n");
        return false;
    }
  
    m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                m_width, m_height, SDL_WINDOW_SHOWN);
}

void Window::ReadConfig() {
    //TODO add config.lua existance check
    std::string title = ConfigSystem::get()->GetString(MAIN_CFG, WIN_TITLE);
    m_title = new char[title.size()+1];
    std::copy(title.begin(), title.end(), m_title);
    m_title[title.size()] = '\0';
    m_width = ConfigSystem::get()->GetInt(MAIN_CFG, WIN_WIDTH);
    if(m_width<=0)
        m_width = 640;
    m_height = ConfigSystem::get()->GetInt(MAIN_CFG, WIN_HEIGHT);
    if(m_height<=0)
        m_height = 480;
    m_fullscreen = ConfigSystem::get()->GetInt(MAIN_CFG, WIN_FULLSCREEN);
}

void Window::EventLoop() {
    if(!m_window) return;
    bool quit = false;
    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent(&e)!=0) {
            switch(e.type) {
            case SDL_QUIT:
                quit = true;
            break;
            default:
            break;
            }
        }
    }
}
