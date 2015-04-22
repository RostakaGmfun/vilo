#include <lua/LuaState.hpp>

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

bool LuaState::DoFile(std::string srcFile) {
    if(!m_state)
        return false;
    if(!srcFile.empty())
        m_srcFile = srcFile;
    
}
