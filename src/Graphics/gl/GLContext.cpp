#include <Window.hpp>
#include <Assert.hpp>
#include <Graphics/gl/GLContext.hpp>

#include <GL/gl.h>

GLContext::GLContext(Window* win, GLContextOptions ops): 
                     m_window(win), m_options(ops) {
            
}

GLContext::~GLContext() {
    Destroy();
}

void GLContext::SetupGLOptions() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, m_options.GLmajor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, m_options.GLminor);
    if(m_options.multisampling) {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        v_ASSERTstr(m_options.numSamples, "[Context::SetupGLOptions] numSamples==0\n");
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, m_options.numSamples);
    }
}

bool GLContext::Init() {
    v_ASSERT(m_window);

    SDL_Window* sdlWin = m_window->GetSDLWin();
    
    v_ASSERT(sdlWin);
    SetupGLOptions();
    m_context = SDL_GL_CreateContext(sdlWin);
    if(!m_context) {
        OS::get()->Log("[Context::Init()] Filed to create GL context. SDL error: %s\n", SDL_GetError());
        return false;
    }

    glClearColor(.2,.2,.2,1);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(m_window->GetSDLWin());
    return true;
}

void GLContext::Destroy() {
    SDL_GL_DeleteContext(m_context);
}
