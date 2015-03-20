#ifndef LUA_STATE_HPP
#define LUA_STATE_HPP

#include <lua5.1/lua.hpp>
#include <string>

class LuaState {
public:
    LuaState();
    LuaState(std::string src);
    void Do(std::string src="");
    
    int GetInt(std::string name);
    std::string GetString(std::string name);
    
    bool SetInt(std::string name, int val);
    bool SetString(std::string name, std::string val);
private:
    bool InitState();

private:
    std::string m_source;
    lua_State* m_state;
};

#endif //LUA_STATE_HPP
