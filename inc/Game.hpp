#ifndef GAME_H
#define GAME_H

#include <vector>

class LuaState;
class Scene;

class Game {
public:
    static Game* get() {
        static Game instance;
        return &instance;
    }

    bool Init();
    bool Update();
    void Destroy();
    Scene* CurrentScene() const { return m_currentScene; }
private:
    Game();
    bool LoadMainScene();
    bool InitLua();

private:
    LuaState* m_lua;
    Scene* m_mainScene;
    Scene* m_currentScene;
    std::vector<Scene*> m_scenes;
};

#endif //GAME_H
