#include <lua/LuaState.hpp>
#include <OS.hpp>

LuaState::LuaState(): m_state(nullptr)
{}

LuaState::LuaState(std::string srcFile): m_state(nullptr), m_srcFile(srcFile)
{}

LuaState::~LuaState() {
    Cleanup();
}

bool LuaState::Init() {
    if(m_state)
        return true;
    
    m_state = lua_open();
    if(!m_state)
        return false;
    luaL_openlibs(m_state);
    return true;
}

void LuaState::Cleanup() {
    if(m_state)
        lua_close(m_state);
}

bool LuaState::DoFile(std::string srcFile) {
    if(!m_state)
        return false;
    if(!srcFile.empty()) {
        m_srcFile = srcFile;
        if(m_srcFile.empty()) {
            OS::get()->Log("[LuaState::DoFile()] No file given");
            return false;
        }
    }
    
    if(luaL_dofile(m_state, m_srcFile.c_str())) {
        OS::get()->Log("[LuaState::DoFile(\"%s\")] failed with error: \"%s\"",
                       m_srcFile.c_str(), Pop<const char*>());
        return false;
    }
    
    return true;
}

void LuaState::DoString(const char* str) {
    if(!m_state)
        return;
    luaL_dostring(m_state, str);
}





