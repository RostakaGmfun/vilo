#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <string>
#include <vector>
#include <map>

class LuaState;

enum VarType {
    VAR_T_STR,
    VAR_T_INT,
    VAR_T_DBL
};

struct EnvVar {
    char *name;
    VarType type;
    union {
        char *strVal;
        int intVal;
        double dblVal;
    };
};

class ConfigSystem {
public:
    static ConfigSystem* get() {
        static ConfigSystem instance;
        return &instance;
    }

    void AddConfigFile(std::string fname);
    void Init(EnvVar* vars, int numVars);
    int GetInt(std::string config, std::string name);
    std::string GetString(std::string config, std::string name);

    LuaState* GetLuaState(std::string configName);
private:
    ConfigSystem(){}
    void SetupEnvironment(EnvVar *vars, int numVars);
private:
    std::vector<std::string> m_configs;
    std::map<std::string,LuaState*> m_states;
};

#endif //CONFIG_HPP
