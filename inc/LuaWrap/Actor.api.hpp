#ifndef ACTOR_API_H
#define ACTOR_API_H

struct lua_State;

namespace vilo {
    int Actor_New(lua_State* L);
    int Actor_Register(lua_State* L);
}

#endif //OS_API_H
