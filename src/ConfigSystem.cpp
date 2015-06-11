#include <ConfigSystem.hpp>
#include <OS.hpp>
#include <FSManager.hpp>
#include <vector>
#include <sstream>
#include <algorithm>

bool ConfigSystem::Init(std::string cfgFname) {
    if(!FSManager::get()->FileExists(cfgFname)) {
        OS::get()->Log("[ConfigSystem::Init] config file %s does not exist\n",
                       cfgFname.c_str());
        return false;
    }
    
    const char* cfg = new char[FSManager::get()->GetFileSize(cfgFname)];
    if(FSManager::get()->ReadFile(cfgFname, (void*)cfg)<=0) {
        OS::get()->Log("[ConfigSystem::Init()] Error reading config file: %s\n", cfgFname.c_str());
        return false;
    }
    std::stringstream input(cfg);
    std::vector<std::string> lines;
    for(std::string line;std::getline(input,line, '\n'); lines.push_back(line)) {
    }

    for(auto i = lines.begin();i!=lines.end();i++) {
        input.clear();
        input.str(*i);
        std::string name, val;
        std::getline(input, name, '=');
        std::getline(input, val, '\n');
        if(name.empty()||val.empty())
            continue;

        name.erase(std::remove_if( name.begin(), name.end(), 
        [](char c){ return (c =='\t' || c == ' ');}), 
                name.end() );

        input.clear();
        input.str(val);

        if(val.find("\"")!=std::string::npos) {
            std::string tmp;
            std::getline(input, tmp, '"');
            std::getline(input, val, '"');
        }
        else
            val.erase(std::remove_if( val.begin(), val.end(), 
                [](char c){ return (c =='\t' || c == ' ');}), 
                    val.end() );

        m_configs[name] = val;
    }
    return true;
}

int ConfigSystem::GetInt(std::string name) {
    if( m_configs.find(name)!=m_configs.end()) {
        return std::stoi(m_configs[name]);
    }
    return 0;
}

std::string ConfigSystem::GetString(std::string name) {
    if( m_configs.find(name)!=m_configs.end()) {
        return m_configs[name];
    }
    return "";
}
