CC=g++
SOURCES= src/OS.cpp src/Window.cpp src/ConfigSystem.cpp src/LuaState.cpp src/InputManager.cpp
CCFLAGS= -I./inc/ -std=c++11
LDFLAGS= -lSDL2 -llua5.1
DEPS=inc/OS.hpp inc/Window.hpp inc/ConfigSystem.hpp inc/LuaState.hpp inc/InputManager.hpp
LIB=bin/libvilo.a
OUT=bin/test
OBJ=$(SOURCES:.cpp=.o)

test: main.cpp lib ;$(CC) $(CCFLAGS) $(LDFLAGS)   main.cpp -o $(OUT) bin/libvilo.a
lib: $(OBJ) ; ar -cvq $(LIB) $(OBJ)

.cpp.o: $(DEPS) ; $(CC) -c $(CCFLAGS) $< -o $@

