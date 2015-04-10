#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SDL2/SDL.h>

class InputManager;

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
};

#endif //WINDOW_HPP
