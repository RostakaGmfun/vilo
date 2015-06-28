#include <OS.hpp>
#include <stdarg.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include <Window.hpp>
#include <ConfigSystem.hpp>
#include <ConfigVars.hpp>
#include <LuaState.hpp>
#include <EventManager.hpp>
#include <Event.hpp>
#include <EventListener.hpp>
#include <Actor.hpp>
#include <TaskManager.hpp>
#include <Game.hpp>
#include <FSManager.hpp>
#include <Graphics/gl/GLContext.hpp>

class EventSniffer: public EventListener {
public:
    EventSniffer(): EventListener(EVT_INPUT) {}
    virtual void HandleEvent(Event *evt) {
        if(!evt)
            return;
        OS::get()->Log("Got event!\n");
    }
};

int OS::Init() {
    FSManager::get()->SetPath("./");   

    if(!Configure())
        return 1;
    
    if(!InitWindow())
        return 1;
    if(!InitContext())
        return 1;
    if(!LoadGame())
        return 1;
 
    m_startTime = SDL_GetTicks();
    return 0;
}

void OS::Log(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int OS::Run() {
    if(!m_window)
        return 1; 
    m_retflag = 0;
    while(true) {
        if(!m_window->EventLoop())
            break;
        TaskManager::get()->Update();
        Uint32 thisTime = SDL_GetTicks();
        float dt = thisTime-m_startTime;
        Game::get()->Update(dt);
        m_startTime  = thisTime;
    }
    return m_retflag;
}

void OS::Cleanup() {
    if(m_window)
        m_window->Quit();
}


bool OS::Configure() {
    return ConfigSystem::get()->Init(MAIN_CFG);
}

int hello(lua_State* state) {
    v_ASSERT(state);
    OS::get()->Log("hello() from C++!\n");
    return 0;
}


bool OS::InitWindow() {
    m_window = new Window();
    return m_window->Init();
}

bool OS::InitContext() {
    if(m_glContext)
        return true;
    if(!m_window)
        return false;
    GLContextOptions ops;
    //default values for now
    ops.GLmajor = 4;
    ops.GLminor = 4;
    ops.multisampling = 0;
    m_glContext = new GLContext(m_window, ops);

    return m_glContext->Init();
}

int OS::Hello(lua_State* state) {
    v_ASSERT(state);
    OS::Log("Hello from lua\n");
    return 0;
}

bool OS::LoadGame() {
    return Game::get()->Init();
}

