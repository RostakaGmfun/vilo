#include <LuaWrap/Actor.api.hpp>
#include <OS.hpp>
#include <LuaState.hpp>
#include <LuaStateMgr.hpp>
#include <lua5.2/lauxlib.h>
#include <FSManager.hpp>
#include <Actor.hpp>

#include <string.h>

namespace vilo {
    int Actor_Hello(lua_State* L) {
        OS::get()->Log("Actor::Hello()\n");
        luaL_checktype(L, 0, LUA_TUSERDATA);
        Actor** a = (Actor**)lua_touserdata(L, 0);
        if(!a)
            luaL_error(L, "[Actor::Hello()]NULL userdata");
        (*a)->Hello();
        return 0;
    }
    int Actor_New(lua_State* L) {
        OS::get()->Log("Actor.New()\n");
        LuaState* ls = LuaStateMgr::get()->GetState(L);
        if(!ls)
            return 0;

        int n = lua_gettop(L);
        if(n<1)
            return luaL_error(L, "[vilo.Actor.New()] Expected arguments");
        std::string fname = FSManager::get()->GetPath()+std::string("actors/")+luaL_checkstring(L, 1);
        std::string name = "unknown";
        if(n>=2)
            name  = luaL_checkstring(L, 2);
//      OS::get()->Log("%s\n", fname.c_str());
        
    //lua code:
    /*function loadenv(file)
        local newenv = {}
        setmetatable(newenv, { __index=_G })
        loadfile(file, bt, newenv)()
        return newenv
    end*/
        lua_newtable(L);

        //setup Actor object as userdata
        lua_pushstring(L, "__object__");
        Actor** a = (Actor**)lua_newuserdata(L, sizeof(Actor*));
        *a = new Actor(fname.c_str(), name, EVT_INPUT);
        lua_settable(L, -3);

        //load actor methods
        static const luaL_Reg methods[] = {
            {"Hello", Actor_Hello },
            {NULL, NULL}
        };

        luaL_setfuncs(L, methods, 0);

//      lua_pushstring(L, "Hello");
//      lua_pushcfunction(L, Actor_Hello);
//      lua_settable(L, -3);

        
        
        return 1;
    }


    int Actor_Register(lua_State* L) {
        static const luaL_Reg Actor_func[] = {
            {"New", Actor_New},
            {NULL, NULL}
        };

        
        luaL_newlib(L, Actor_func);
        
        
        return 1;
    }
}
