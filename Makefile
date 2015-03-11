CC=g++
SOURCES=main.cpp src/OS.cpp src/Window.cpp src/ConfigSystem.cpp src/LuaState.cpp src/FSManager.cpp
CCFLAGS= -I./inc/ -std=c++11
LDFLAGS= -lSDL2 -llua5.1
DEPS=inc/OS.hpp inc/Window.hpp inc/ConfigSystem.hpp inc/LuaState.hpp inc/FSManager.hpp
OUT=bin/horror
OBJ=$(SOURCES:.cpp=.o)

all: $(OBJ) ; $(CC) $(LDFLAGS) $(OBJ) -o $(OUT)

.cpp.o: $(SOURCES) $(DEPS) ; $(CC) -c $(CCFLAGS) $< -o $@
