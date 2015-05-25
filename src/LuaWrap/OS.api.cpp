#include <LuaWrap/OS.api.hpp>
#include <OS.hpp>
#include <LuaState.hpp>
#include <LuaStateMgr.hpp>
#include <lua5.2/lauxlib.h>

namespace vilo {
    int OS_Hello(lua_State* L) {
        OS::get()->Log("[OS.Hello()]\n");
        return 0;
 
    }

    int OS_Register(lua_State* L) {
        static const luaL_Reg OS_func[] = {
            {"Hello", OS_Hello},
            {NULL, NULL}
        };


        if(!L)
            return 1;
        luaL_newlib(L, OS_func);
//        lua_setfield(L, -2, "__index");
//        lua_settable(L, -2);
        return 1;
    }
}
