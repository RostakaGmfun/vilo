#ifndef WINDOW_API_H
#define WINDOW_API_H

struct lua_State;

namespace vilo {
   int Window_Quit(lua_State* L);


   int Window_Register(lua_State* L);
}

#endif //WINDOW_API_H
