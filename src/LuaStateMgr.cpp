#include <LuaStateMgr.hpp>
#include <LuaState.hpp>

void LuaStateMgr::RegisterState(LuaState* state) {
    if(!state)
        return;
    m_states[state->GetState()] = state;
}

LuaState* LuaStateMgr::GetState(lua_State *state) {
    if(m_states.find(state)!=m_states.end())
        return m_states[state];
    return NULL;
}
