#ifndef LUA_API_H
#define LUA_API_H

class LuaState;

class LuaAPI {
public:
   virtual void RegisterAPI(LuaState *state) = 0;
};

#endif //LUA_API_H
