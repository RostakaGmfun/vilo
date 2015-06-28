#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include <EventListener.hpp>

class Context: public EventListener {
public:
    Context(): EventListener(EVT_WINDOW) {}
    virtual ~Context() {}

    virtual bool Init() = 0;
    virtual void Destroy() = 0;

    virtual void HandleEvent(Event* evt);
protected:
    virtual void Resize(int width, int height) = 0;
};

#endif //CONTEXT_HPP
