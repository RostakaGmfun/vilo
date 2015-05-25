#include <LuaWrap/Window.api.hpp>
#include <OS.hpp>
#include <Window.hpp>
#include <lua5.2/lua.hpp>

namespace vilo {
    int Window_Quit(lua_State* L) {
        Window* win = OS::get()->GetCurrentWindow();
        
        if(!win) {
            OS::get()->Log("[window.Quit()]: error! NULL window\n");
            return 0;
        }
        win->Quit();
        return 0;
    }



   int Window_Register(lua_State* L) {
        static const luaL_Reg Window_func[] {
            {"Quit", Window_Quit},
            {NULL, NULL}
        };

        if(!L)
            return 0;
        luaL_newlib(L, Window_func);
 //       lua_setfield(L, -2, "__index");
 //       lua_settable(L, -2);
        return 1;
   }
}
