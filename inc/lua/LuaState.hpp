#ifndef LUA1_STATE_HPP
#define LUA1_STATE_HPP

#include <string>
#include <lua/lua.hpp>

namespace Lua_detail {

    template<typename T> 
    void stack_Push(T, lua_State* state);

    template<typename T>
    T stack_Pop(lua_State* state);
    
    template<typename T>
    T get_Var(const char* varName, lua_State* state);

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
}

class LuaState {
public:
    LuaState(std::string srcFile);
    LuaState();
    ~LuaState();
  
    bool Init();
    void Cleanup();

    //execution
    bool DoFile(std::string srcFile="");
    void DoString(const char* str);


    //low level stack manipulations
    template<typename T> 
    void Push(T val) {
        Lua_detail::stack_Push<T>(val, m_state);
    }

    
    template<typename T>
    T Pop() {
        return Lua_detail::stack_Pop<T>(m_state);
    }

    template<typename T>
    T GetVar(const char* varName) {
        return Lua_detail::get_Var<T>(varName,m_state);
    }

private:

private:
    lua_State* m_state;
    std::string m_srcFile;
};

#endif //LUA1_STATE_HPP
