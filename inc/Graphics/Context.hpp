#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SDL2/SDL_video.h>

class Window;

struct ContextOptions {
    unsigned int GLmajor;
    unsigned int GLminor;
    bool multisampling;
    unsigned int numSamples;
};

class Context {
public:
    Context(Window* win);
    ~Context();

    bool Init(ContextOptions ops);
    void Destroy();

private:
    void SetupGLOptions(ContextOptions ops);

private:
    Window* m_window;
    SDL_GLContext m_context;
};

#endif //CONTEXT_HPP
