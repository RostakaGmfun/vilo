#include <LuaWrap/Actor.api.hpp>
#include <OS.hpp>
#include <LuaState.hpp>
#include <LuaStateMgr.hpp>
#include <lua5.2/lauxlib.h>
#include <FSManager.hpp>
#include <Actor.hpp>
#include <Game.hpp>
#include <Scene.hpp>

#include <string.h>

namespace vilo {
    
    int Actor_Hello(lua_State* L) {
        OS::get()->Log("Actor::Hello()\n");
        luaL_checktype(L, -1, LUA_TTABLE);
        lua_getfield(L, -1, "__object__"); 
        Actor** a = (Actor**)lua_touserdata(L, -1);
        if(!a)
            luaL_error(L, "[Actor::Hello()] NULL userdata");
        (*a)->Hello();
        return 0;
    }

    static std::string fname_to_load = "";

    int Actor_LoadScript(lua_State* L) {
        const char* fname = lua_tostring(L, -1);
        OS::get()->Log("%s\n", fname);
        LuaState* ls = LuaStateMgr::get()->GetState(L);
        if(!ls)
            luaL_error(L, "State not registered\n");
        ls->DoFile(fname);
        return 0;
    }

    int Actor_New(lua_State* L) {
        LuaState* ls = LuaStateMgr::get()->GetState(L);
        if(!ls)
            return 0;

        int n = lua_gettop(L);
        if(n<1)
            return luaL_error(L, "[vilo.Actor.New()] Expected arguments");
        std::string actorClass = luaL_checkstring(L, 1);
        std::string fname = FSManager::get()->GetPath()+std::string("actors/")+actorClass;
        std::string name = "unknown";
        if(n>=2)
            name  = luaL_checkstring(L, 2);

        if(FSManager::get()->FileExists(fname+".lua"))
            fname+=".lua";
        else
            if(FSManager::get()->FileExists(fname+".luac"))
                fname+=".luac";
        else {
            OS::get()->Log("[vilo.Actor.New()] Could not find actor '%s'\n", actorClass.c_str());
            return 0;
        }
        lua_getglobal(L, "loadenv");
        lua_pushstring(L, fname.c_str());
        lua_call(L, 1, 1);
        
        //setup Actor object as userdata
        lua_pushstring(L, "__object__"); //table "__object__"
        Actor** a = (Actor**)lua_newuserdata(L, sizeof(Actor*)); // table "__object__" usr_data
        *a = new Actor(ls, name, EVT_INPUT, Game::get()->CurrentScene());
        lua_settable(L, -3); //table
        
        //load actor methods
        static const luaL_Reg methods[] = {
            {"Hello", Actor_Hello },
            {NULL, NULL}
        };

        luaL_setfuncs(L, methods, 0); //table
        
        lua_pushlightuserdata(L, (void*)(*a)); //table lightuserdata
        lua_pushvalue(L, -2); //table lightuserdata table
        // registryindex[*a]=actor_luatable
        lua_settable(L, LUA_REGISTRYINDEX); //table

        Game::get()->CurrentScene()->AddActor(*a);
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
