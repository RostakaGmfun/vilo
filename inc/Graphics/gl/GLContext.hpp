#ifndef GLCONTEXT_HPP
#define GLCONTEXT_HPP

#include <Graphics/Context.hpp>

#include <SDL2/SDL_video.h>

class Window;

struct GLContextOptions {
    unsigned int GLmajor;
    unsigned int GLminor;
    bool multisampling;
    unsigned int numSamples;
};

class GLContext: public Context {
public:
    GLContext(Window* win, GLContextOptions ops);
    ~GLContext();

    bool Init();
    void Destroy();

private:
    void SetupGLOptions();

private:
    Window* m_window;
    SDL_GLContext m_context;
    GLContextOptions m_options;
};

#endif //GLCONTEXT_HPP
