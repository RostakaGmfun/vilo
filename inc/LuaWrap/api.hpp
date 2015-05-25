#ifndef API_H
#define API_H

#include <LuaWrap/OS.api.hpp>
#include <LuaWrap/Window.api.hpp>

struct lua_State;

bool RegisterModules(lua_State* L);

#endif //API_H
