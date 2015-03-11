#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SDL2/SDL.h>

class Window {
public:
    Window();
    bool Init();
    void EventLoop();

private:
    void ReadConfig();

private:
    SDL_Window* m_window;
    char* m_title;
    int m_width;
    int m_height;
    bool m_fullscreen;
};

#endif //WINDOW_HPP
