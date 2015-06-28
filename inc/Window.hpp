#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <Event.hpp>

#include <SDL2/SDL.h>

class InputManager;

class ResizeEvent: public Event {
public:
    ResizeEvent(int w, int h): Event(EVT_WINDOW, EVT_RESIZE), width(w), height(h) {}
    int width;
    int height;
};

class Window {
public:
    Window();
    bool Init();
    int EventLoop(); //0 to exit, 1 to continue
    void Quit();
    SDL_Window* GetSDLWin() const { return m_window; }
private:
    void ReadConfig();

private:
    SDL_Window* m_window;
    char* m_title;
    int m_width;
    int m_height;
    bool m_fullscreen;
    int m_quit;
};

#endif //WINDOW_HPP
