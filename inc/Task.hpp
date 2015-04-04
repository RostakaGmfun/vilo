#ifndef TASK_HPP
#define TASK_HPP

enum TASK_FLAGS {
    TASK_SINGLESHOT = 0,
    TASK_REPEATED = 1<<1
};

class Task {
public:
    Task(const char *name, int priority, TASK_FLAGS flags):
        m_name(name), m_priority(priority), m_flags(flags) {}
    //virtual ~Task(); //never understood why the virtual destructors are needed. 
    //will leave it for now
    virtual bool Init() = 0;
    virtual int Run() = 0;
    TASK_FLAGS GetFlags() const { return m_flags; }
protected:
    const char* m_name;
    int m_priority;
    TASK_FLAGS m_flags;
    bool m_initialized;
};

#endif //TASK_HPP
