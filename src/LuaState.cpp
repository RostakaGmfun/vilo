#include <LuaState.hpp>
#include <OS.hpp>
#include <luabind/luabind.hpp>

LuaState::LuaState(): m_source(""), m_state(NULL)  {
    InitState();
}

LuaState::LuaState(std::string src): m_source(src), m_state(NULL)  {
    InitState();
}

bool LuaState::InitState() {
    if(m_state)
        return true;
    m_state = lua_open();
    if(!m_state)
        return false;
    luabind::open(m_state);
    luaL_openlibs(m_state);
}

bool LuaState::Do(std::string src) {
    if(!m_state) {
        return false;
    }
    if(!src.empty())
        m_source = src;
    if(luaL_dofile(m_state, m_source.c_str())) {
        OS::get()->Log("[LuaState::Do()]: failed to do file %s with error: \"%s\"\n",
        src.c_str(),lua_tostring(m_state, -1));
        return false;
    }
    return true;
}

void LuaState::DoString(std::string str) {
    if(!m_state)
        return;
    luaL_dostring(m_state, str.c_str());
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
        OS::get()->Log("[LuaState::GetInt()]: Trying to get %s as integer failed!\n", name.c_str());
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
        OS::get()->Log("[LuaState::GetString()]: Trying to get %s as string failed!\n", name.c_str());
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
        OS::get()->Log("[LuaState::GetDouble()]: Trying to get %s as double failed!\n", name.c_str());
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

Argument LuaState::Call(std::string funcName, std::vector<Argument> args) {
    if(!m_state) {
        OS::get()->Log("[LuaState::Call()]: not initialised\n");
        return Argument((int)0);
    }
    lua_getglobal(m_state, funcName.c_str());
    
    if(!lua_isfunction(m_state, lua_gettop(m_state))) {
        OS::get()->Log("[LuaState::Call()]: function \"%s\" not declared!\n",funcName.c_str());
        return Argument(0);
    }

    for(auto i = args.begin();i!=args.end();i++) {
        switch(i->t) {
            case ARG_INT:
                lua_pushnumber(m_state, i->intVal);
                break;
            case ARG_DBL:
                lua_pushnumber(m_state, i->dblVal);
                break;
            case ARG_STR:
                lua_pushstring(m_state, i->strVal.c_str());
                break;
        }
    }
    lua_call(m_state, args.size(), 1);
    if(lua_isnil(m_state, -1))
        return Argument(0);
    if(lua_isnumber(m_state,-1)) {
        double n = lua_tonumber(m_state, -1);
        if(n==(int)n) //integer
            return Argument((int)n);
        else
            return Argument(n);
    }

    if(lua_isstring(m_state, -1))
        return Argument(lua_tostring(m_state, -1));
}


Argument LuaState::PCall(std::string funcName, std::vector<Argument> args) {
    if(!m_state) {
        OS::get()->Log("[LuaState::Call()]: not initialised\n");
        return Argument((int)0);
    }
    lua_getglobal(m_state, funcName.c_str());
    
    if(!lua_isfunction(m_state, lua_gettop(m_state))) {
        OS::get()->Log("[LuaState::Call()]: function \"%s\" not declared!\n",funcName.c_str());
        return Argument(0);
    }

    for(auto i = args.begin();i!=args.end();i++) {
        switch(i->t) {
            case ARG_INT:
                lua_pushnumber(m_state, i->intVal);
                break;
            case ARG_DBL:
                lua_pushnumber(m_state, i->dblVal);
                break;
            case ARG_STR:
                lua_pushstring(m_state, i->strVal.c_str());
                break;
        }
    }
    int ret = lua_pcall(m_state, args.size(), 1, 0);
    if(ret) {
        if(ret = LUA_ERRRUN) {
            OS::get()->Log("[LuaState::PCall()] Error running script %s\n\tErr msg: \"%s\"\n", m_source.c_str(), lua_tostring(m_state, -1));
            return Argument(0);
        }
        else {
            OS::get()->Log("[LuaState::PCall()] Memory allocation error in %s\n\tErr msg: \"%s\"\n", m_source.c_str(), lua_tostring(m_state, -1));
            return Argument(0); 
        }
    }
    if(lua_isnil(m_state, -1))
        return Argument(0);
    if(lua_isnumber(m_state,-1)) {
        double n = lua_tonumber(m_state, -1);
        if(n==(int)n) //integer
            return Argument((int)n);
        else
            return Argument(n);
    }

    if(lua_isstring(m_state, -1))
        return Argument(lua_tostring(m_state, -1));
}

void LuaState::Cleanup() {
    if(!m_state)
        return;
    lua_close(m_state);
}

bool LuaState::RegisterFunc(LuaFunction f, std::string name) {
    if(!m_state)
        return false;
    lua_register(m_state, name.c_str(), (lua_CFunction)f);
}
