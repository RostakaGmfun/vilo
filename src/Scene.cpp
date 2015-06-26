#include <Scene.hpp>
#include <LuaState.hpp>

Scene::Scene(LuaState* state, std::string name, int EvtMask, std::string src):
            Actor(state, name, EvtMask), m_src(src)
{}

bool Scene::Init() {
    v_ASSERT(m_state);
    if(!m_state->DoFile(m_src)) {
        OS::get()->Log("[Scene::Init] Error running scene script!\n");
        return false;
    }
    return !m_state->PCall<int>("create");
}

void Scene::Update(float dt) {
    v_ASSERT(m_state);
    m_state->Call<void>("update", dt);
    for(auto i = m_actors.begin(); i != m_actors.end(); i++) {
        (*i)->Update(dt);
    }
}

void Scene::Destroy() {
    if(!m_state)
        return;
    m_state->Call<void>("destroy");
}

void Scene::AddActor(Actor* a) {
    m_actors.push_back(a);
}
