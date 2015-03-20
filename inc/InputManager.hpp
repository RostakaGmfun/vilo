#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP
#include <vector>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_events.h>

class Window;
struct KeyboardEvent {
    KeyboardEvent(SDL_Keycode k, bool p):key(k), pressed(p)  {}
    SDL_Keycode key;
    bool pressed; //if true that was a keypress, else - keyrelease
};

struct MouseEvent {
    MouseEvent(int _x, int _y,bool *_state):x(_x), y(_y) {
        if(_state)
            for(int i = 0;i<3;i++)
                state[i] = _state[i];
    }
    int x;
    int y;
    bool state[3];
};

typedef void (*KeyboardCallback)(KeyboardEvent ev);
typedef void (*MouseCallback)(MouseEvent ev);

class InputManager {
public:
    static InputManager *get() {
        static InputManager instance;
        return &instance;
    }
    bool Init(Window *win);
    int MouseX();
    int MouseY();
    bool MouseDown(int button); //0=LMB,1=MMB, 2=RMB
    bool KeyDown(SDL_Keycode key);
    void SetMouseCallback(MouseCallback cb) { m_mouse_callback = cb; }
    void SetKBCallback(KeyboardCallback cb) { m_kb_callback = cb; }
    void ProcessEvent(SDL_Event ev);
private:
    InputManager():m_kb_callback(NULL), m_mouse_callback(NULL) {}

private:
    Window *m_client;
    KeyboardCallback m_kb_callback;
    MouseCallback m_mouse_callback;
    std::vector<SDL_Keycode> m_kbState;
    bool m_mouseState[3]; //0 - LMB, 1 - MMB, 2 - RMB
    int m_mouseX;
    int m_mouseY;
};
#endif //INPUT_MANAGER_HPP
