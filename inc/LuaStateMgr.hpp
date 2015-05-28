#ifndef LUA_STATE_MGR_H
#define LUA_STATE_MGR_H

#include <map>
#include <lua5.2/lua.hpp>
class LuaState;

class LuaStateMgr {
public:
    static LuaStateMgr* get() {
        static LuaStateMgr instance;
        return &instance;
    }

    void RegisterState(LuaState* state);
    LuaState* GetState(lua_State *state);
private:
    LuaStateMgr() {}

private:
    std::map<lua_State*, LuaState*> m_states;
};

#endif //LUA_STATE_MGR_H

