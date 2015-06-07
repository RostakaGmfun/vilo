#include <LuaState.hpp>
#include <OS.hpp>
#include <Assert.hpp>
#include <LuaWrap/api.hpp>
#include <FSManager.hpp>

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
    
    m_state = luaL_newstate();
    v_ASSERT(m_state);
    luaL_openlibs(m_state);
    
    if(!LoadDetail()) {
        OS::get()->Log("[LuaState::Init()] Error loading detail\n");
        return false;
    }
    
    if(!LoadModules()) {
        OS::get()->Log("[LuaState::Init()] Error loading modules!\n");
        return false;
    }

    return true;
}

bool LuaState::LoadModules() {
    if(!m_state)
        return false;
    lua_newtable(m_state);
    lua_setglobal(m_state, "vilo");
    RegisterModules(m_state);
    return true;
}

bool LuaState::LoadDetail() {
    if(!m_state)
        return false;
    std::string fpath = FSManager::get()->GetPath();
    fpath+="scripts/";
    SetVar("_Path", fpath.c_str());
    if(!DoFile(fpath+"detail/init.lua"))
        return false;
    return true;
}

void LuaState::Cleanup() {
    if(m_state)
        lua_close(m_state);
}

bool LuaState::DoFile(std::string srcFile) {
    v_ASSERT(m_state);
    if(!srcFile.empty()) {
        m_srcFile = srcFile;
        if(m_srcFile.empty()) {
            OS::get()->Log("[LuaState::DoFile()] No file given\n");
            return false;
        }
    }
    
    if(luaL_dofile(m_state, m_srcFile.c_str())) {
        OS::get()->Log("[LuaState::DoFile(\"%s\")] failed with error: \"%s\"\n",
                       m_srcFile.c_str(), Get<const char*>());
        return false;
    }
    return true;
}

void LuaState::DoString(const char* str) {
    v_ASSERT(m_state);
    if(luaL_dostring(m_state, str)) {
        OS::get()->Log("[LuaState::DoString()] failed with error \"%s\"\n", 
                Get<const char*>());
    }
}

void  LuaState::RegisterFunc(LuaFunction func, const char* funcName) {
    v_ASSERT(m_state);
    lua_register(m_state, funcName, func); 
}



