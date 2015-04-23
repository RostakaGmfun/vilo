#ifndef LUA1_STATE_HPP
#define LUA1_STATE_HPP

#include <string>
#include <lua/Lua_detail.hpp>


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
    /*template<typename T> 
    void Push(T val) {
        Lua_detail::stack_Push<T>(val, m_state);
    }*/

    //template<>
    void Push(int val) {
        if(!m_state)
            return;
        lua_pushinteger(m_state, val);
    }

    //template<>
    void Push(double val) {
        if(!m_state)
            return;
        lua_pushnumber(m_state,val);
    }

    //template<>
    void Push(std::string val) {
        if(!m_state)
            return;
        lua_pushstring(m_state,val.c_str());
    }

    //template<>
    void Push(const char* val) {
        if(!m_state)
            return;
        lua_pushstring(m_state, val);
    }
    
    template<typename T>
    T Pop() {
        return Lua_detail::stack_Pop<T>(m_state);
    }

    template<typename T>
    T GetVar(const char* varName) {
        return Lua_detail::get_Var<T>(varName,m_state);
    }
    
    void SetVar(const char* varName, int val) {
        if(!m_state)
            return;
        lua_pushinteger(m_state, val);
        lua_setglobal(m_state, varName);
        return;
    }
    
    void SetVar(const char* varName, double val) {
        if(!m_state)
            return;
        lua_pushnumber(m_state, val);
        lua_setglobal(m_state, varName);
    }

    void SetVar(const char* varName, const char* val) {
        if(!m_state)
            return;
        lua_pushstring(m_state, val);
        lua_setglobal(m_state, varName);

    }

private:

private:
    lua_State* m_state;
    std::string m_srcFile;
};

#endif //LUA1_STATE_HPP
