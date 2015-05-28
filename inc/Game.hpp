#ifndef GAME_H
#define GAME_H

class LuaState;

class Game {
public:
    Game();

    bool Init();
    bool Update();
    void Destroy();

private:
    bool LoadMainScene();
    bool InitLua();

private:
    LuaState *m_lua;
};

#endif //GAME_H
