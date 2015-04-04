#include <OS.hpp>
#include <stdarg.h>
#include <stdio.h>

#include <ConfigSystem.hpp>
#include <ConfigVars.hpp>
#include <LuaState.hpp>
#include <EventManager.hpp>
#include <Event.hpp>
#include <EventListener.hpp>

//will write dumb event sniffer which listens to all events, later will move it somwhere else...

class EventSniffer: protected EventListener {
public:
    EventSniffer(): EventListener(EVT_INPUT) {}
    virtual void HandleEvent(Event *evt) {
        if(!evt)
            return;
        OS::get()->Log("Got event!\n");
    }
};

int OS::Init() {
    InitSystems();
}

void OS::Log(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void OS::InitSystems() {
    ConfigSystem::get()->AddConfigFile(MAIN_CFG);
    EnvVar* vars = new EnvVar[2];
    vars[0].type=VAR_T_STR;
    vars[0].name="EngineCodename";
    vars[0].strVal="WizleyGrizley";
    vars[1].type=VAR_T_INT;
    vars[1].name="testvar";
    vars[1].intVal=1;
    ConfigSystem::get()->Init(vars, 2);
    LuaState* st = ConfigSystem::get()->GetLuaState("config.lua");
    std::vector<Argument> args;
    args.push_back(2);
    args.push_back(3);
    Argument ret = st->PCall("test",args);
    Log("Result: %i\n",ret.intVal);
    EventSniffer *sniffer = new EventSniffer();
    EventManager::get()->AddListener((EventListener*)sniffer);
}
