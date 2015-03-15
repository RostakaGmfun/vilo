#include <OS.hpp>
#include <stdarg.h>
#include <stdio.h>

#include <ConfigSystem.hpp>
#include <ConfigVars.hpp>

int OS::Main() {
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
    ConfigSystem::get()->Init();
}
