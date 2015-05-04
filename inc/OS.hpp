#ifndef OS_HPP
#define OS_HPP

//#include <LuaAPI.hpp>

class LuaState;
class Window;
struct lua_State;

class OS {
public:
    static OS* get() {
        static OS instance;
        return &instance;
    }
    //LuaState* GetGState() const { return globalState; }
    int Init(); //returns 0 on success and nonzero on failure
    int Run(); // return 0 to exit and 1 to restart
    void Cleanup();
    void Log(const char* format, ...);
    int Hello(lua_State*);
    void RegisterAPI(LuaState *state);
    //static LuaState *globalState;
private:
    OS(): m_window(nullptr), m_retflag(0) {}
    //int InitSystems();
    bool Configure();
    bool InitWindow();
private:
    Window* m_window;
    int m_retflag;
};


#endif //OS_HPP
