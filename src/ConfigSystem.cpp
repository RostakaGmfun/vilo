#include <ConfigSystem.hpp>
#include <OS.hpp>

void ConfigSystem::AddConfigFile(std::string fname) {
    m_configs.push_back(fname);
}

void ConfigSystem::Init() {    
    for(int i = 0;i<m_configs.size();i++) {
        m_states[m_configs[i]] = new LuaState(m_configs[i]);
        m_states[m_configs[i]]->Do();
    }
}

int ConfigSystem::GetInt(std::string config, std::string name) {
   for(auto i = m_states.begin(); i!=m_states.end();i++) {
        if(i->first==config)
            return i->second->GetInt(name);
   }
   return 0;
}

std::string ConfigSystem::GetString(std::string config, std::string name) {
    for(auto i = m_states.begin(); i!=m_states.end();i++) {
        if(i->first==config)
            return i->second->GetString(name);
    }
    return "";
}


