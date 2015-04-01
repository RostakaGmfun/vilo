#include <TaskManager.hpp>
#include <Task.hpp>
#include <OS.hpp>

void TaskManager::AddTask(Task* task) {
    if(!task)
        return;
    m_tasks.push_back(task);
    task->Init();
}

void TaskManager::Update() {
    for(auto i = m_tasks.begin();i!=m_tasks.end();++i) {
        Task *t = *i;
        if(t->GetFlags() & TASK_SINGLESHOT) { //run only once
            t->Run();
            m_tasks.erase(i);
        }
        else
            t->Run();
    }
}
