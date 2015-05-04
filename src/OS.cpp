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

//will write dumb event sniffer which listens to all events, later will move it somwhere else...

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
    if(!Configure())
        return 1;
    if(!InitWindow())
        return 1;
    Actor *a = new Actor("scripts/actor.lua", "MyLittleActor", EVT_INPUT);
    TaskManager::get()->AddTask(a);
 
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
    }
    return m_retflag;
}

void OS::Cleanup() {
    if(m_window)
        m_window->Quit();
}

/*void OS::InitSystems() {
    LuaState* st = ConfigSystem::get()->GetLuaState("config.lua");
    std::vector<Argument> args;
    args.push_back(2);
    args.push_back(3);
    Argument ret = st->PCall("test",args);
    Log("Result: %i\n",ret.intVal); 
    Actor *a = new Actor("scripts/actor.luac", "MyLittleActor");
    TaskManager::get()->AddTask(a);
    EventSniffer *sniffer = new EventSniffer();
    EventManager::get()->AddListener(sniffer);
}*/

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
    LuaState* st = new LuaState("scripts/actor.lua");
    st->Init();
    st->DoFile();
    int ret = st->Call<int>("add", 2, 3);
    Log("%i\n", ret);
    st->Call<void>("greeting", "Rost", 17 );
    st->RegisterFunc(hello, "hello");
    st->Call<void>("create");
    m_window = new Window();
    return m_window->Init();
}

int OS::Hello(lua_State* state) {
    v_ASSERT(state);
    OS::Log("Hello from lua\n");
    return 0;
}


//#include <api/OS.api>
