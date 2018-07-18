#ifndef PYTHONMODULE_H_4FJ8GRHD
#define PYTHONMODULE_H_4FJ8GRHD

#include <iostream>

class CanPythonModule {
public:
    void setPorts(int portsNumber)
    {

        std::cerr << "aa" << std::endl;
       _ports = portsNumber;
    }

private:
    int _ports;
};
#endif /* end of include guard: PYTHONMODULE_H_4FJ8GRHD */
