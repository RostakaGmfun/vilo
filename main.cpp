#include <OS.hpp>
#include <Window.hpp>

int main() {
    OS::get()->Main();
    Window* win = new Window();
    win->Init();
    win->EventLoop();
    return 0;
}
