#include <OS.hpp>

int main() {
    if(OS::get()->Init())
        return 0;
    int ret = 0;
    /*while(OS::get()->Run()) {
        OS::get()->Cleanup();
        if(OS::get()->Init())
            break;
    }*/
    OS::get()->Run();
    OS::get()->Cleanup();
    return 0;
}
