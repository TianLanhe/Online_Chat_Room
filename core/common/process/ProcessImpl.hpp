#ifndef PROCESS_IMPL_HPP
#define PROCESS_IMPL_HPP

#include "../include/process/Process.hpp"
#include <unistd.h>
#include <string>
#include <vector>

class ProcessImpl : public Process{
public:
	ProcessImpl(const std::string&);
	ProcessImpl(const std::vector<std::string>&);
	ProcessImpl(int (*)(void*));
        ~ProcessImpl();

	Status Start();
        Status Terminate();

	Status GetExitCode(int*);

	Status WaitFor();

private:
        void _setCommand();
        bool _hasTerminate();

	bool m_bTerminate;
        bool m_bHasWait;
	pid_t m_pid;

};

Process* GetProcessImpl(int (*)(void*));
Process* GetProcessImpl(const std::vector<std::string>&);

#endif

