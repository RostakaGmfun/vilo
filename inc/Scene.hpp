#ifndef SCENE_H
#define SCENE_H

#include <Actor.hpp>

#include <vector>

class Scene: public Actor {
public:
    Scene(LuaState* state, std::string name,int EvtMask, std::string src);
    virtual bool Init();
    virtual void Update(float dt);
    virtual void Destroy();

    void AddActor(Actor* a);
private:
    std::vector<Actor*> m_actors;
    std::string m_src;
};


#endif //SCENE_H
