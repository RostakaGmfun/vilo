#ifndef LUA_STATE_HPP
#define LUA_STATE_HPP

#include <string>
#include <Lua_detail.hpp>
#include <typeinfo>
#include <OS.hpp>

struct lua_State;

typedef int (*LuaFunction) (lua_State* state);

class LuaState {
public:
    LuaState(std::string srcFile);
    LuaState();
    ~LuaState();
  
    bool Init();
    void Cleanup();
    lua_State* GetState() const { return m_state; }

    //execution
    bool DoFile(std::string srcFile="");
    void DoString(const char* str);

    template<typename Ret, typename ... Args>
    Ret Call(const char* funcName, Args ... args) {
        v_ASSERT(m_state);
        lua_getglobal(m_state, funcName);

        if(!lua_isfunction(m_state, lua_gettop(m_state))) {
            OS::get()->Log("[LuaState::Call()]: function \"%s\" "
                           "not declared!\n",funcName);
        v_ASSERTstr(false, "Attempt to call undeclared lua function");
        return (Ret)0;
    }
        PushParams(args...);
        
        if(typeid(Ret)==typeid(void)) {
            lua_call(m_state, sizeof...(args), 0);
            return (Ret)0;
        }

        lua_call(m_state, sizeof...(args), 1); 
        return Lua_detail::stack_Pop<Ret>(m_state);
    }

    template<typename Ret>
    Ret Call(const char* funcName) {
        v_ASSERT(m_state);
        lua_getglobal(m_state, funcName);

        if(!lua_isfunction(m_state, lua_gettop(m_state))) {
            OS::get()->Log("[LuaState::Call()]: function \"%s\" "
                           "not declared!\n",funcName);
        v_ASSERTstr(false, "Attempt to call undeclared lua function");
        return (Ret)0;
    }
        if(typeid(Ret)==typeid(void)) {
            lua_call(m_state, 0, 0);
            return (Ret)0;
        }
        lua_call(m_state,0, 1); 
        return Lua_detail::stack_Pop<Ret>(m_state);
    }

    template<typename Ret, typename ... Args>
    Ret PCall(const char* funcName, Args ... args) {
        v_ASSERT(m_state);
        lua_getglobal(m_state, funcName);

        if(!lua_isfunction(m_state, lua_gettop(m_state))) {
            OS::get()->Log("[LuaState::Call()]: function \"%s\" "
                           "not declared!\n",funcName);
        v_ASSERTstr(false, "Attempt to call undeclared lua function");
        return (Ret)0;
    }
        PushParams(args...);
        if(typeid(Ret)==typeid(void)) {
            lua_pcall(m_state, sizeof...(args), 0, 0);
            return (Ret)0;
        }

        lua_pcall(m_state, sizeof...(args), 1, 0); 
        return Lua_detail::stack_Pop<Ret>(m_state);
    }

    template<typename Ret>
    Ret PCall(const char* funcName) {
        v_ASSERT(m_state);
        lua_getglobal(m_state, funcName);

        if(!lua_isfunction(m_state, lua_gettop(m_state))) {
            OS::get()->Log("[LuaState::Call()]: function \"%s\" "
                           "not declared!\n",funcName);
        v_ASSERTstr(false, "Attempt to call undeclared lua function");
        return (Ret)0;
    }
        if(typeid(Ret)==typeid(void)) {
            lua_pcall(m_state, 0, 0, 0);
            return (Ret)0;
        }
        lua_pcall(m_state,0, 1, 0); 
        return Lua_detail::stack_Pop<Ret>(m_state);
    }
     
    void RegisterFunc(LuaFunction func, const char* funcName);

    //stack manipulation
    inline void Push(int val) {
        v_ASSERT(m_state);
        lua_pushinteger(m_state, val);
    }

    inline void Push(double val) {
        v_ASSERT(m_state);
        lua_pushnumber(m_state,val);
    }

    inline void Push(std::string val) {
        v_ASSERT(m_state);
        lua_pushstring(m_state,val.c_str());
    }

    inline void Push(const char* val) {
        v_ASSERT(m_state);
        lua_pushstring(m_state, val);
    }
    
    template<typename T>
    inline T Get() {
        return Lua_detail::stack_Get<T>(m_state);
    }
   
    template<typename T>
    inline T GetVar(const char* varName) {
        return Lua_detail::get_Var<T>(varName,m_state);
    }
    
    inline void SetVar(const char* varName, int val) {
        lua_pushinteger(m_state, val);
        lua_setglobal(m_state, varName);
    }
    
    inline void SetVar(const char* varName, double val) {
        lua_pushnumber(m_state, val);
        lua_setglobal(m_state, varName);
    }

    inline void SetVar(const char* varName, const char* val) {
        lua_pushstring(m_state, val);
        lua_setglobal(m_state, varName);
    }

    template<typename T>
    inline void PushParams(T v) {
        v_ASSERT(m_state);
        Push(v);
    }

    template<typename T, typename ... Args>
    inline void PushParams(T v, Args ... args) {
        v_ASSERT(m_state);
        Push((T)v);
        PushParams(args...);
    }

private:
    bool LoadModules();
    bool LoadDetail();

private:
    lua_State* m_state;
    std::string m_srcFile;
};

#endif //LUA_STATE_HPP
