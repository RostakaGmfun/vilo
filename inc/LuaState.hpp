#ifndef LUA_STATE_HPP
#define LUA_STATE_HPP

#include <Task.hpp>

#include <lua/lua.hpp>
#include <string>
#include <vector>

class LuaState;

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

typedef int (*LuaFunction)(LuaState* state);
typedef int (*lua_CFunction)(lua_State* state);

class LuaState {
public:
    LuaState();
    LuaState(std::string src);

    //operator lua_State*() { return m_state; }
    lua_State* GetState() const { return m_state; }
    void SetSrc(std::string src);
    std::string GetSrc() const { return m_source; }
    bool Do(std::string src="");
    void DoString(std::string str);

    int GetInt(std::string name);
    std::string GetString(std::string name);
    double GetDouble(std::string name);
    
    bool SetInt(std::string name, int val);
    bool SetString(std::string name, std::string val);
    bool SetDouble(std::string name, double val);

    Argument Call(std::string funcName, std::vector<Argument> args = std::vector<Argument>());
    Argument PCall(std::string funcName, std::vector<Argument> args = std::vector<Argument>()); // protected call

    bool RegisterFunc(LuaFunction f, std::string name);

    void Cleanup();
private:
    bool InitState();

private:
    std::string m_source;
    lua_State* m_state;
};

#endif //LUA_STATE_HPP
