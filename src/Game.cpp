#include <Game.hpp>
#include <LuaState.hpp>
#include <LuaStateMgr.hpp>
#include <FSManager.hpp>

Game::Game(): m_lua(nullptr)
{}

bool Game::Init() {
    if(!InitLua()) {
        OS::get()->Log("[Game::Init()]: Error initialising Lua\n");
        return false;
    }
    if(!LoadMainScene()) {
        OS::get()->Log("[Game::Init()]: Error loading Main scene\n");
        return false;
    }
    return true;
}

bool Game::Update() {

    return true;
}

void Game::Destroy() {

}

bool Game::InitLua() {
    if(m_lua)
        return true;
    m_lua = new LuaState();
    if(!m_lua->Init()) return false;
    LuaStateMgr::get()->RegisterState(m_lua);
    return true;
}

bool Game::LoadMainScene() {
    if(!m_lua)
        return false;
    bool compiled = false;
    if(!FSManager::get()->FileExists("scenes/Main.lua")) {
        if(!FSManager::get()->FileExists("scenes/Main.luac")) {
            return false;
        }
        else {
            compiled = true;
        }
    }
    if(compiled)
        m_lua->DoFile("scenes/Main.luac");
    else
        m_lua->DoFile("scenes/Main.lua");
    return true;
}

