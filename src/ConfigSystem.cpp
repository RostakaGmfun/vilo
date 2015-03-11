#include <ConfigSystem.hpp>

void ConfigSystem::AddConfigFile(std::string fname) {
    m_configs.push_back(fname);
}

void ConfigSystem::Init() {
    m_state = new LuaState();
}

int ConfigSystem::GetInt(std::string config, std::string name) {
    if(!m_state)
        Init();
    m_state->Do(config);
    return  m_state->GetInt(name);
}

std::string ConfigSystem::GetString(std::string config, std::string name) {
    if(!m_state)
        Init();
    m_state->Do(config);
    return  m_state->GetString(name);
}


