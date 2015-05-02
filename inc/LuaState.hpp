#ifndef LUA1_STATE_HPP
#define LUA1_STATE_HPP

#include <string>
#include <Lua_detail.hpp>
#include <typeinfo>
#include <OS.hpp>

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

    template<typename Ret, typename ... Args>
    Ret Call(const char* funcName, Args ... args ) {
        v_ASSERT(m_state);
        lua_getglobal(m_state, funcName);
    
         if(!lua_isfunction(m_state, lua_gettop(m_state))) {
            OS::get()->Log("[LuaState::Call()]: function \"%s\" "
                           "not declared!\n",funcName);
            return (Ret)0;
    }
        PushParams(args...);
        lua_call(m_state, sizeof...(args), 1); 
        return Get<Ret>();
    }

    //low level stack manipulations
    /*template<typename T> 
    void Push(T val) {
        Lua_detail::stack_Push<T>(val, m_state);
    }*/

    //template<>
    void Push(int val) {
        v_ASSERT(m_state);
        lua_pushinteger(m_state, val);
    }

    //template<>
    void Push(double val) {
        v_ASSERT(m_state);
        lua_pushnumber(m_state,val);
    }

    //template<>
    void Push(std::string val) {
        v_ASSERT(m_state);
        lua_pushstring(m_state,val.c_str());
    }

    //template<>
    void Push(const char* val) {
        v_ASSERT(m_state);
        lua_pushstring(m_state, val);
    }
    
    template<typename T>
    T Get() {
        return Lua_detail::stack_Get<T>(m_state);
    }
    
    template<typename T>
    T Pop() {
        T v = Lua_detail::stack_Get<T>(m_state);
        lua_pop(m_state, 1);
        return v;
    }

    template<typename T>
    T GetVar(const char* varName) {
        return Lua_detail::get_Var<T>(varName,m_state);
    }
    
    void SetVar(const char* varName, int val) {
        lua_pushinteger(m_state, val);
        lua_setglobal(m_state, varName);
    }
    
    void SetVar(const char* varName, double val) {
        lua_pushnumber(m_state, val);
        lua_setglobal(m_state, varName);
    }

    void SetVar(const char* varName, const char* val) {
        lua_pushstring(m_state, val);
        lua_setglobal(m_state, varName);
    }

    /*template<typename T>
    inline T PushParams(T v) {
        return v;
    }

    template<typename T, typename ... Args>
    inline T PushParams(T v,Args... args) {
        OS::get()->Log("before...\n");
        OS::get()->Log("after!\n");
        if(!this)
            OS::get()->Log("are you fucking kidding me???\n");
        //Lua_detail::push_Params(m_state, args...);

    }*/

    template<typename T>
    inline void PushParams(T v) {
        v_ASSERT(m_state);
        Push(v);
    }

    template<typename T, typename ... Args>
    inline void PushParams(T v, Args ... args) {
        v_ASSERT(m_state);
        /*if(typeid(v)==typeid(int)) {
            //Push(v);
            //lua_pushinteger(m_state, v);
            //OS::get()->Log("%i\n",v);
        }
        if(typeid(v)==typeid(double)) {
            //Push(v);
            //lua_pushnumber(m_state, v);
            //OS::get()->Log("%f\n",v);
        }
        if(typeid(v)==typeid(const char*)) {
            //lua_pushstring(m_state, v);
            //OS::get()->Log("string %s\n",v);
        }*/
    //    OS::get()->Log("ddd\n");
        Push((T)v);
//        OS::get()->Log("asd\n");
        PushParams(args...);
}

private:

private:
    lua_State* m_state;
    std::string m_srcFile;
};

#endif //LUA1_STATE_HPP
