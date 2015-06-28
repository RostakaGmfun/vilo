cmake_minimum_required(VERSION 2.8)

add_library(vilo STATIC src/OS.cpp src/Window.cpp src/ConfigSystem.cpp
    src/InputManager.cpp src/TaskManager.cpp src/EventManager.cpp
    src/Actor.cpp src/LuaState.cpp src/LuaStateMgr.cpp 
    src/FSManager.cpp src/Game.cpp src/Scene.cpp src/Graphics/Context.cpp
    src/Graphics/gl/GLContext.cpp src/Graphics/gl/GLAPI.cpp


    src/LuaWrap/api.cpp src/LuaWrap/OS.api.cpp src/LuaWrap/Window.api.cpp
    src/LuaWrap/Actor.api.cpp)


include_directories(inc/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(vilo-game)

add_executable(vilo-game main.cpp)
target_link_libraries(vilo-game vilo lua5.2 SDL2)
