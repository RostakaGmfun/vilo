#include <ConfigSystem.hpp>
#include <OS.hpp>
#include <LuaState.hpp>

void ConfigSystem::AddConfigFile(std::string fname) {
    m_configs.push_back(fname);
}

void ConfigSystem::Init(EnvVar *vars, int numVars) {    
    for(int i = 0;i<m_configs.size();i++)
        m_states[m_configs[i]] = new LuaState(m_configs[i]);
    SetupEnvironment(vars, numVars);
    for(int i = 0;i<m_configs.size();i++)
        m_states[m_configs[i]]->Do();
}

void ConfigSystem::SetupEnvironment(EnvVar *vars, int numVars) {
    if(!vars)
        return;
    for(auto i = m_states.begin();i!=m_states.end();i++) {
        for(int j = 0;j<numVars;j++) {
            switch(vars[j].type) {
            case VAR_T_STR:
                OS::get()->Log("[ConfigSystem] Setting env var: %s=%s\n",vars[j].name,vars[j].strVal);
                i->second->SetString(vars[j].name, vars[j].strVal);
            break;
            case VAR_T_INT:
                OS::get()->Log("[ConfigSystem] Setting env var: %s=%i\n", vars[j].name, vars[j].intVal);
                i->second->SetInt(vars[j].name, vars[j].intVal);
            break;
            case VAR_T_DBL:
                
            break;
            }
        }
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

LuaState* ConfigSystem::GetLuaState(std::string configName) {
    for(auto i = m_states.begin(); i!=m_states.end();i++) {
        if(i->first==configName)
            return i->second;
    }
    return NULL;
}
