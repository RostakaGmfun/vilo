#ifndef LUA_STATE_HPP
#define LUA_STATE_HPP

#include <Task.hpp>

#include <lua5.1/lua.hpp>
#include <string>
#include <vector>


enum ARG_TYPE {
    ARG_INT,
    ARG_DBL,
    ARG_STR
};

struct Argument {
    Argument(int val):t(ARG_INT), intVal(val)  {}
    Argument(double val): t(ARG_DBL), dblVal(val) {}
    Argument(std::string val): t(ARG_STR), strVal(val) {}
    ARG_TYPE t;
    int intVal;
    double dblVal;
    std::string strVal;
};

class LuaState: public Task {
public:
    //LuaState();
    LuaState(std::string src);
    void SetSrc(std::string src);
    std::string GetSrc() const { return m_source; }
    void Do(std::string src="");
    
    virtual bool Init();
    virtual int Run();

    int GetInt(std::string name);
    std::string GetString(std::string name);
    double GetDouble(std::string name);
    
    bool SetInt(std::string name, int val);
    bool SetString(std::string name, std::string val);
    bool SetDouble(std::string name, double val);

    Argument Call(std::string funcName, std::vector<Argument> args);
    Argument PCall(std::string funcName, std::vector<Argument> args); // protected call
private:
    bool InitState();

private:
    std::string m_source;
    lua_State* m_state;
};

#endif //LUA_STATE_HPP
