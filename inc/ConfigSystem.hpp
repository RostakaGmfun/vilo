#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <string>
#include <vector>
#include <map>

#include <LuaState.hpp>

enum CONFIG_VAR_T {
    CONFIG_TINT = 1,
    CONFIG_TSTR
};

struct ConfigVar {
    CONFIG_VAR_T type;
    std::string config;
    union {
        std::string str;
        int num;
    };
};

class ConfigSystem {
public:
    static ConfigSystem* get() {
        static ConfigSystem instance;
        return &instance;
    }

    void AddConfigFile(std::string fname);
    void Init();
    int GetInt(std::string config, std::string name);
    std::string GetString(std::string config, std::string name);

private:
    ConfigSystem(){}

private:
    std::vector<std::string> m_configs;
    std::vector<ConfigVar*> m_vars;
    std::map<std::string,LuaState*> m_states;
};

#endif //CONFIG_HPP
