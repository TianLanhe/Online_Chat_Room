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

	Status Start();
	Status Destroy();

	Status GetExitCode(int*);

	Status WaitFor();

private:
	bool m_bTerminate;
	pid_t m_pid;

};

#endif

