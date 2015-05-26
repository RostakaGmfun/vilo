#include <LuaWrap/api.hpp>
#include <lua5.2/lua.hpp>

bool RegisterModules(lua_State* L)  {
    if(!L)
        return false;
    lua_getglobal(L, "vilo");
    luaL_requiref(L, "OS", vilo::OS_Register, 1);
    lua_setfield(L, -2, "OS");
//    lua_pop(L, 1);
    luaL_requiref(L, "Window", vilo::Window_Register, 1);
    lua_setfield(L, -2, "Window");
//    lua_pop(L, 1);
    return true;
}
