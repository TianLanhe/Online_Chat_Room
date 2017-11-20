#ifndef PROCESS_IMPL_HPP
#define PROCESS_IMPL_HPP

#include "../include/process/Process.hpp"
#include <unistd.h>
#include <string>
#include <vector>

class ProcessImpl : public Process{
public:
        explicit ProcessImpl(const std::vector<std::string>&);
        explicit ProcessImpl(int (*)(void*),void* arg = NULL);
        ~ProcessImpl();

	Status Start();
        Status Destroy();
        bool isDestroy(){ return _hasDestroy(); }

	Status GetExitCode(int*);

	Status WaitFor();

private:
        bool _hasDestroy();

        bool m_bDestroy;
        int m_exitCode;
	pid_t m_pid;

        int (*m_func)(void*);
        void *m_arg;

        std::vector<std::string> m_com;

};

Process* GetProcessImpl(int (*)(void*),void*);
Process* GetProcessImpl(const std::vector<std::string>&);

#endif

