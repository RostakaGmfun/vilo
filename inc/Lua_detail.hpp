#ifndef LUA_DETAIL
#define LUA_DETAIL
#include <lua5.2/lua.hpp>
#include <typeinfo>
#include <OS.hpp>
#include <Assert.hpp>
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

    template<typename T>
    inline T push_Params(lua_State* state, T v) {
        v_ASSERT(state);
        return v;
    }

    template<typename T, typename ... Args>
    inline T push_Params(lua_State* state, T v, Args ... args) {
        v_ASSERT(state);
        //OS::get()->Log("before\n");
        //this->m_state = NULL;
        //OS::get()->Log("after\n");
        if(typeid(v)==typeid(int)) {
            //Push(v);
            lua_pushinteger(state, v);
           // OS::get()->Log("%i\n",v);
        }
        if(typeid(v)==typeid(double)) {
            //Push(v);
            lua_pushnumber(state, v);
            //OS::get()->Log("%f\n",v);
        }
        /*if(typeid(v)==typeid(std::string)) {
            lua_pushstring(m_state, v.c_str());
            OS::get()->Log("%s\n", v.c_str());
        }*/
        if(typeid(v)==typeid(const char*)) {
            //lua_pushstring(m_state, v);
            //OS::get()->Log("%s\n",v);
        }
    //    OS::get()->Log("ddd\n");
  //      Push(v);
        OS::get()->Log("asd\n");
//        push_Params(state, args...);
}

}

#endif //LUA_DETAIL
