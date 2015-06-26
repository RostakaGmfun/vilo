#include <Graphics/Context.hpp>

#include <Window.hpp>
#include <Assert.hpp>

Context::Context(Window* win): m_window(win) {
            
}

Context::~Context() {
    Destroy();
}

void Context::SetupGLOptions(ContextOptions ops) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, ops.GLmajor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, ops.GLminor);
    if(ops.multisampling) {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        v_ASSERTstr(ops.numSamples, "[Context::SetupGLOptions] numSamples==0\n");
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, ops.numSamples);
    }
}

bool Context::Init(ContextOptions ops) {
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

void Context::Destroy() {
    SDL_GL_DeleteContext(m_context);
}
