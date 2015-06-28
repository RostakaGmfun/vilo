#include <Graphics/Context.hpp>

#include <Window.hpp>

void Context::HandleEvent(Event* evt) {
    if(!evt)
        return;
    switch(evt->GetType()) {
        case EVT_RESIZE: {
            ResizeEvent *resize = (ResizeEvent*)evt;
            Resize(resize->width, resize->height);
        }
    }
}
