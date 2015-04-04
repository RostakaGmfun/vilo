#include <TaskManager.hpp>
#include <Task.hpp>
#include <OS.hpp>

void TaskManager::AddTask(Task* task) {
    if(!task)
        return;
    if(!task->Init())
        return;
    m_tasks.push_back(task);
}

void TaskManager::Update() {
    for(auto i = m_tasks.begin();i!=m_tasks.end();++i) {
        Task *t = *i;
        if(t->GetFlags() & TASK_SINGLESHOT) { //run only once
            t->Run();
            m_tasks.erase(i);
        }
        else {
            int ret = t->Run(); 
            if(ret) {
                OS::get()->Log("[TaskManager] Task returned error code %i", ret);
            }
        }
    }
}
