#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <vector>

class Task;

class TaskManager {
public:
    static TaskManager* get() {
        static TaskManager instance;
        return &instance;
    }

    void AddTask(Task* task);
    void Update();

private:
    TaskManager() {}

private:
    std::vector<Task*> m_tasks;
};

#endif //TASK_MANAGER_HPP
