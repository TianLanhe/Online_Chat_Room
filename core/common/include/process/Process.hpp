#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "../DataStructureBase.hpp"

class Process{
public:
	virtual ~Process(){}

	virtual Status Start() = 0;
	virtual Status Destroy() = 0;

	virtual Status WaitFor() = 0;	

	virtual Status GetExitCode(int*) = 0;

private:
	int m_exitCode;
};

#endif

