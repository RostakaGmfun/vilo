#include <Game.hpp>
#include <LuaState.hpp>
#include <LuaStateMgr.hpp>
#include <FSManager.hpp>
#include <Scene.hpp>

Game::Game(): m_lua(nullptr), m_mainScene(nullptr), m_currentScene(nullptr)
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
    v_ASSERT(m_currentScene);
    m_currentScene->Update(0);
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
    std::string src = FSManager::get()->GetPath()+"scenes/Main.lua";
    if(!FSManager::get()->FileExists("scenes/Main.lua")) {
        if(!FSManager::get()->FileExists("scenes/Main.luac")) {
            return false;
        }
        else {
            compiled = true;
            src = FSManager::get()->GetPath()+"scenes/Main.luac";
        }
    }

    m_mainScene = new Scene(m_lua,"Main",  EVT_INPUT,src );
    m_currentScene = m_mainScene;
    return m_mainScene->Init();
}
