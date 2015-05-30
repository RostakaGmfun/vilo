#include <LuaWrap/api.hpp>
#include <lua5.2/lua.hpp>

#include <LuaWrap/OS.api.hpp>
#include <LuaWrap/Window.api.hpp>
#include <LuaWrap/Actor.api.hpp>

bool RegisterModules(lua_State* L)  {
    if(!L)
        return false;
    lua_getglobal(L, "vilo");
    luaL_requiref(L, "OS", vilo::OS_Register, 1);
    lua_setfield(L, -2, "OS");
    
    luaL_requiref(L, "Window", vilo::Window_Register, 1);
    lua_setfield(L, -2, "Window");
    

    luaL_requiref(L, "Actor", vilo::Actor_Register, 1);
    lua_setfield(L, -2, "Actor");

    return true;
}
