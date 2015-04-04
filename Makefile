CC=g++
SOURCES= src/OS.cpp src/Window.cpp src/ConfigSystem.cpp src/LuaState.cpp \
    src/InputManager.cpp src/TaskManager.cpp src/EventManager.cpp
CCFLAGS= -I./inc/ -std=c++11 -g
LDFLAGS= -lSDL2 -llua5.1 
DEPS=inc/OS.hpp inc/Window.hpp inc/ConfigSystem.hpp inc/LuaState.hpp \
     inc/InputManager.hpp inc/TaskManager.hpp inc/Event.hpp inc/EventManager.hpp \
     inc/Task.hpp
LIB=bin/libvilo.a
OUT=bin/test
OBJ=$(SOURCES:.cpp=.o)

test: main.cpp lib ;$(CC) $(CCFLAGS) $(LDFLAGS)  main.cpp -o $(OUT) $(LIB)
lib: $(DEPS) $(OBJ) ;rm $(LIB); ar -q $(LIB) $(OBJ); ar -s $(LIB)

.cpp.o: $(DEPS) ; $(CC) -c $(CCFLAGS)  $< -o $@

