#ifndef LUA_DETAIL
#define LUA_DETAIL
#include <typeinfo>
#include <OS.hpp>
#include <Assert.hpp>
#include <lua5.2/lua.hpp>
namespace Lua_detail {

    template<typename T> 
    void stack_Push(T, lua_State* state);

    template<typename T>
    T stack_Get(lua_State* state);
    
    template<typename T>
    T get_Var(const char* varName, lua_State* state);

    template<typename T>
    void set_Var(const char* varName, T val, lua_State* state);

    template<>
    inline void stack_Push(int val, lua_State* state) {
        v_ASSERT(state);
        lua_pushinteger(state, val);
    }

    template<>
    inline void stack_Push(double val, lua_State* state) {
        v_ASSERT(state);
        lua_pushnumber(state,val);
    }

    template<>
    inline void stack_Push(std::string val, lua_State* state) {
        v_ASSERT(state);
        lua_pushstring(state,val.c_str());
    }

    template<>
    inline void stack_Push(const char* val, lua_State* state) {
        v_ASSERT(state);
        lua_pushstring(state, val);
    }

    template<>
    inline int stack_Get(lua_State* state) {
        v_ASSERT(state);
        return lua_tointeger(state, lua_gettop(state));
    }
    
    template<>
    inline void stack_Get(lua_State* state) {
    }

    template<>
    inline double stack_Get(lua_State* state) {
        v_ASSERT(state);
        return lua_tonumber(state, lua_gettop(state));
    }

    template<>
    inline std::string stack_Get(lua_State* state) {
        v_ASSERT(state);
        return std::string(lua_tostring(state, lua_gettop(state)));
    }

    template<>
    inline const char* stack_Get(lua_State* state) {
        v_ASSERT(state);
        return lua_tostring(state, lua_gettop(state));
    }
    
    template<>
    inline int get_Var(const char* varName, lua_State* state) {
        v_ASSERT(state);
        lua_getglobal(state, varName);

        int ret = 0;

        if(lua_isnumber(state, lua_gettop(state)))
            ret = lua_tointeger(state, lua_gettop(state));
        return ret;
    }
    
    template<>
    inline double get_Var(const char* varName, lua_State* state) {
        v_ASSERT(state);
        lua_getglobal(state, varName);

        double ret = 0;

        if(lua_isnumber(state, lua_gettop(state)))
            ret = lua_tonumber(state, lua_gettop(state));
        return ret;
    }
    
    template<>
    inline std::string get_Var(const char* varName, lua_State* state) {
        v_ASSERT(state);
        lua_getglobal(state, varName);

        std::string ret;

        if(lua_isstring(state, lua_gettop(state)))
            ret = lua_tostring(state, lua_gettop(state));
        return ret;
    }

    template<>
    inline void set_Var(const char* varName, int val, lua_State* state) {
        v_ASSERT(state);
        lua_pushinteger(state, val);
        lua_setglobal(state, varName);
        return;
    }
    
    template<>
    inline void set_Var(const char* varName, double val, lua_State* state) {
        v_ASSERT(state);
        lua_pushnumber(state, val);
        lua_setglobal(state, varName);
    }

    template<>
    inline void set_Var(const char* varName, const char* val, lua_State* state) {
        v_ASSERT(state);
        lua_pushstring(state, val);
        lua_setglobal(state, varName);
    }
}

#endif //LUA_DETAIL
