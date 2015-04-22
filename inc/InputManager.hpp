#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP
#include <Event.hpp>

#include <vector>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_events.h>
#include <string>

class Window;
class KeyboardEvent: public Event {
public:
    KeyboardEvent(SDL_Keycode k, bool p): Event(EVT_INPUT, EVT_KB), key(k), pressed(p) {}
    SDL_Keycode key;
    bool pressed; //if true that was a keypress, else - keyrelease
};

struct MouseEvent: public Event {
public:
    MouseEvent(int _x, int _y,int _press, bool _down): Event(EVT_INPUT, EVT_MOUSE), x(_x), y(_y), press(_press), down(_down) {}
    int x;
    int y;
    int press; //0 - LMB, 1 - MMB, 2 - RMB
    bool down; //true if button press, false if release
};

typedef void (*KeyboardCallback)(KeyboardEvent* ev);
typedef void (*MouseCallback)(MouseEvent* ev);

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
    std::string ToLuaKey(KeyboardEvent* evt);
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
