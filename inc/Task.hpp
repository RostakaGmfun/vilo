#ifndef TASK_HPP
#define TASK_HPP

enum TASK_FLAGS {
    TASK_SINGLESHOT = 0,
    TASK_REPEATED = << 1<<1
}

class Task {
public:
    Task(int priority, TASK_FLAGS flags);
    virtual ~Task();
    virtual void Init() = 0;
    virtual int Run() = 0;

private:
    int m_priority;
    TASK_FLAGS flags;
    bool m_initialized;
};

#endif //TASK_HPP
