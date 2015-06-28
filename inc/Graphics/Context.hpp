#ifndef CONTEXT_HPP
#define CONTEXT_HPP

class Context {
public:
    Context() {}
    virtual ~Context() {}

    virtual bool Init() = 0;
    virtual void Destroy() = 0;
};

#endif //CONTEXT_HPP
