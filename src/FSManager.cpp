#include <FSManager.hpp>
#include <stdio.h>

bool FSManager::FileExists(std::string fname) {
    if(FILE* f = fopen(std::string(m_path+fname).c_str(), "r")) {
        fclose(f);
        return true;
    }
    else
        return false;
}

int FSManager::GetFileSize(std::string fname) {
    if(FILE* f = fopen(std::string(m_path+fname).c_str(), "r")) {
        fseek(f, 0, SEEK_END);
        int ret = ftell(f);
        fclose(f);
        return ret;
    }
    else
        return -1;
}

int FSManager::ReadFile(std::string fname, void* buf) {
    if(!buf)
        return -1;
    if(FILE* f = fopen(fname.append(m_path).c_str(), "r")) {
        fseek(f, 0, SEEK_END);
        int sz = ftell(f);
        fseek(f, 0, SEEK_SET);
        return fread(buf, sz, 1, f);
    }
    else
        return -1;
}


