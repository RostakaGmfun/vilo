#include <OS.hpp>
#include <stdarg.h>
#include <stdio.h>

#include <Window.hpp>
#include <ConfigSystem.hpp>
#include <ConfigVars.hpp>
#include <LuaState.hpp>
#include <EventManager.hpp>
#include <Event.hpp>
#include <EventListener.hpp>
#include <Actor.hpp>
#include <TaskManager.hpp>
#include <LuaClass.hpp>
#include <Game.hpp>
#include <FSManager.hpp>

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

    if(!LoadGame())
        return 1;

//    Actor *a = new Actor("scripts/actor.lua", "MyLittleActor", EVT_INPUT);
 
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
        v_ASSERT(m_game);
        m_game->Update();
    }
    return m_retflag;
}

void OS::Cleanup() {
    if(m_window)
        m_window->Quit();
}


bool OS::Configure() {
    ConfigSystem::get()->AddConfigFile(MAIN_CFG);
    EnvVar* vars = new EnvVar[2];
    vars[0].type=VAR_T_STR;
    vars[0].name="Codename";
    vars[0].strVal="WizleyGrizley";
    vars[1].type=VAR_T_INT;
    vars[1].name="testvar";
    vars[1].intVal=1;
    return ConfigSystem::get()->Init(vars, 2);
}

int hello(lua_State* state) {
    v_ASSERT(state);
    OS::get()->Log("hello() from C++!\n");
    return 0;
}


bool OS::InitWindow() {
    st = new LuaState("scripts/actor.lua");
    st->Init();
    st->DoFile();
    int ret = st->Call<int>("add", 2, 3);
    Log("%i\n", ret);
    st->Call<void>("greeting", "Rost", 17 );
    st->RegisterFunc(hello, "hello");
    m_window = new Window();
    st->Call<void>("create");
    return m_window->Init();
}

int OS::Hello(lua_State* state) {
    v_ASSERT(state);
    OS::Log("Hello from lua\n");
    return 0;
}

bool OS::LoadGame() {
    if(m_game)
        return true;
    m_game = new Game();
    return m_game->Init();
}
