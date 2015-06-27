#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SDL2/SDL_video.h>

class Window;

struct GLContextOptions {
    unsigned int GLmajor;
    unsigned int GLminor;
    bool multisampling;
    unsigned int numSamples;
};

class GLContext {
public:
    GLContext(Window* win);
    ~GLContext();

    bool Init(GLContextOptions ops);
    void Destroy();

private:
    void SetupGLOptions(GLContextOptions ops);

private:
    Window* m_window;
    SDL_GLContext m_context;
};

#endif //CONTEXT_HPP
