#ifndef OS_HPP
#define OS_HPP

class LuaState;
class Window;
class GLContext;
struct lua_State;

class OS {
public:
    static OS* get() {
        static OS instance;
        return &instance;
    }
    int Init(); //returns 0 on success and nonzero on failure
    int Run(); // return 0 to exit and 1 to restart
    void Cleanup();
    void Log(const char* format, ...);
    int Hello(lua_State*);
    void RegisterAPI(LuaState *state);
    Window* GetCurrentWindow() const { return m_window; }
private:
    OS(): m_window(nullptr), m_retflag(0), m_glContext(nullptr) {}
    bool Configure();
    bool InitWindow();
    bool LoadGame();
    bool InitContext();
private:
    Window* m_window;
    int m_retflag;
    unsigned int m_startTime;
    GLContext* m_glContext;
};


#endif //OS_HPP
