#ifndef OS_HPP
#define OS_HPP

class OS {
public:
    static OS* get() {
        static OS instance;
        return &instance;
    }

    int Init();
    void Log(const char* format, ...);

private:
    OS() {}
    void InitSystems();

private:    
};


#endif //OS_HPP
