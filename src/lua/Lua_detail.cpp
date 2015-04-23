#include <lua/Lua_detail.hpp>

namespace Lua_detail {

    template<>
    void stack_Push(int val, lua_State* state) {
        if(!state)
            return;
        lua_pushinteger(state, val);
    }

    template<>
    void stack_Push(double val, lua_State* state) {
        if(!state)
            return;
        lua_pushnumber(state,val);
    }

    template<>
    void stack_Push(std::string val, lua_State* state) {
        if(!state)
            return;
        lua_pushstring(state,val.c_str());
    }

    template<>
    void stack_Push(const char* val, lua_State* state) {
        if(!state)
            return;
        lua_pushstring(state, val);
    }

    template<>
    int stack_Pop(lua_State* state) {
        if(!state)
            return 0;
        return lua_tointeger(state, lua_gettop(state));
    }

    template<>
    double stack_Pop(lua_State* state) {
        if(!state)
            return 0;
        return lua_tonumber(state, lua_gettop(state));
    }

    template<>
    std::string stack_Pop(lua_State* state) {
        if(!state)
            return "";
        return lua_tostring(state, lua_gettop(state));
    }

    template<>
    int get_Var(const char* varName, lua_State* state) {
        if(!state)
            return 0;
        lua_getglobal(state, varName);

        int ret = 0;

        if(lua_isnumber(state, lua_gettop(state)))
            ret = lua_tointeger(state, lua_gettop(state));
        return ret;
    }
    
    template<>
    double get_Var(const char* varName, lua_State* state) {
        if(!state)
            return 0;
        lua_getglobal(state, varName);

        double ret = 0;

        if(lua_isnumber(state, lua_gettop(state)))
            ret = lua_tonumber(state, lua_gettop(state));
        return ret;
    }
    
    template<>
    std::string get_Var(const char* varName, lua_State* state) {
        if(!state)
            return 0;
        lua_getglobal(state, varName);

        std::string ret;

        if(lua_isstring(state, lua_gettop(state)))
            ret = lua_tostring(state, lua_gettop(state));
        return ret;
    }

    template<>
    void set_Var(const char* varName, int val, lua_State* state) {
        if(!state)
            return;
        lua_pushinteger(state, val);
        lua_setglobal(state, varName);
        return;
    }
    
    template<>
    void set_Var(const char* varName, double val, lua_State* state) {
        if(!state)
            return;
        lua_pushnumber(state, val);
        lua_setglobal(state, varName);
    }

    template<>
    void set_Var(const char* varName, const char* val, lua_State* state) {
        if(!state)
            return;
        lua_pushstring(state, val);
        lua_setglobal(state, varName);

    }
}
