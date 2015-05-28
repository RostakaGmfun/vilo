#ifndef FS_MANAGER_HPP
#define FS_MANAGER_HPP
#include <string>

class FSManager {
public:
    static FSManager* get() {
        static FSManager instance;
        return &instance;
    }
    
    void SetPath(std::string path) { m_path = path; }
    bool FileExists(std::string fname);
    std::string GetPath() const { return m_path; }
    int GetFileSize(std::string fname);
    int ReadFile(std::string fname, void* buf);

private:
    FSManager() {}

private:
    std::string m_path;
};

#endif //FS_MANAGER_HPP
