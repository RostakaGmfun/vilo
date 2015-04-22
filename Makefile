CC=g++
SOURCES= src/OS.cpp src/Window.cpp src/ConfigSystem.cpp src/LuaState.cpp \
    src/InputManager.cpp src/TaskManager.cpp src/EventManager.cpp \
    src/Actor.cpp src/lua/LuaState.cpp
CCFLAGS= -I./inc/ -std=c++11
LDFLAGS= -lSDL2 -llua5.1 -lluabind
DEPS=inc/OS.hpp inc/Window.hpp inc/ConfigSystem.hpp inc/LuaState.hpp \
     inc/InputManager.hpp inc/TaskManager.hpp inc/Event.hpp inc/EventManager.hpp \
     inc/Task.hpp inc/Actor.hpp inc/lua/LuaState.hpp
LIB=bin/libvilo.a
OUT=bin/test
OBJ=$(SOURCES:.cpp=.o)

test: main.cpp lib ;$(CC) $(CCFLAGS) $(LDFLAGS)  main.cpp -o $(OUT) $(LIB)
lib: $(DEPS) $(OBJ) $(LDFLAGS) ;rm $(LIB); ar -q $(LIB) $(OBJ); ar -s $(LIB)

.cpp.o: $(DEPS) ; $(CC) -c $(CCFLAGS) $(LDFLAGS)  $< -o $@

clean: ; rm src/*.o; rm src/lua/*.o
