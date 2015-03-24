#include <LuaState.hpp>
#include <OS.hpp>

LuaState::LuaState(): m_source(""), m_state(NULL) {
    InitState();
}

LuaState::LuaState(std::string src): m_source(src), m_state(NULL) {
    InitState();
}

bool LuaState::InitState() {
    if(m_state)
        return true;
    m_state = lua_open();
    if(!m_state)
        return false;

    luaL_openlibs(m_state);
}

void LuaState::Do(std::string src) {
    if(!m_state)
        return;
    if(!src.empty())
        m_source = src;
    if(luaL_dofile(m_state, m_source.c_str())) {
        OS::get()->Log("LuaState::Do(): failed to do file %s with error: \"%s\"\n",
        src.c_str(),lua_tostring(m_state, -1));
    }
}

int LuaState::GetInt(std::string name) {
    if(!m_state)
        return 0;
    lua_getglobal(m_state, name.c_str());
    
    int val = 0;
    if(lua_isnumber(m_state, lua_gettop(m_state))) {
        val = lua_tonumber(m_state, lua_gettop(m_state));
    }
    else
        OS::get()->Log("LuaState::GetInt(): Trying to get %s as integer failed!\n", name.c_str());
    return val;
}

std::string LuaState::GetString(std::string name) {
    if(!m_state)
        return 0;
    lua_getglobal(m_state, name.c_str());
    
    std::string val = "";
    if(lua_isstring(m_state, -1)) {
        val = lua_tostring(m_state, -1);
    }
    else
        OS::get()->Log("LuaState::GetString(): Trying to get %s as string failed!\n", name.c_str());
    return val;
}

double LuaState::GetDouble(std::string name) {
    if(!m_state)
        return 0;
    lua_getglobal(m_state, name.c_str());
    
    double val = 0;
    if(lua_isnumber(m_state, lua_gettop(m_state))) {
        val = lua_tonumber(m_state, lua_gettop(m_state));
    }
    else
        OS::get()->Log("LuaState::GetDouble(): Trying to get %s as double failed!\n", name.c_str());
    return val;
}

bool LuaState::SetInt(std::string name, int val) {
    if(!m_state)
        return false;
    lua_pushnumber(m_state, val);
    lua_setglobal(m_state, name.c_str());
    return true;
}

bool LuaState::SetString(std::string name, std::string val) {
    if(!m_state)
        return false;
    lua_pushstring(m_state, val.c_str());
    lua_setglobal(m_state, name.c_str());
    return true;
}

bool LuaState::SetDouble(std::string name, double val) {
    if(!m_state)
        return false;
    lua_pushnumber(m_state, val);
    lua_setglobal(m_state, name.c_str());
    return true;
}
