#include <Graphics/GLContext.hpp>

#include <Window.hpp>
#include <Assert.hpp>

GLContext::GLContext(Window* win): m_window(win) {
            
}

GLContext::~GLContext() {
    Destroy();
}

void GLContext::SetupGLOptions(GLContextOptions ops) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, ops.GLmajor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, ops.GLminor);
    if(ops.multisampling) {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        v_ASSERTstr(ops.numSamples, "[Context::SetupGLOptions] numSamples==0\n");
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, ops.numSamples);
    }
}

bool GLContext::Init(GLContextOptions ops) {
    v_ASSERT(m_window);

    SDL_Window* sdlWin = m_window->GetSDLWin();
    
    v_ASSERT(sdlWin);
    SetupGLOptions(ops);
    m_context = SDL_GL_CreateContext(sdlWin);
    if(!m_context) {
        OS::get()->Log("[Context::Init()] Filed to create GL context. SDL error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void GLContext::Destroy() {
    SDL_GL_DeleteContext(m_context);
}
