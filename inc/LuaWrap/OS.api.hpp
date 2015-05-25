#ifndef OS_API_H
#define OS_API_H

struct lua_State;

namespace vilo {
    int OS_Hello(lua_State* L);
    int OS_Register(lua_State* L);
}

#endif //OS_API_H
