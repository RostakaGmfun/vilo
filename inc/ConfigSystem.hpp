#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <string>
#include <map>

class ConfigSystem {
public:
    static ConfigSystem* get() {
        static ConfigSystem instance;
        return &instance;
    }

    bool Init(std::string cfgFname);
    int GetInt(std::string name);
    std::string GetString(std::string name);

private:
    ConfigSystem(){}
private:
    std::string m_cfgFname;
    std::map<std::string,std::string> m_configs;
};

#endif //CONFIG_HPP
