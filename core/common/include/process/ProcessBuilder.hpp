#ifndef PROCESS_BUILDER_HPP
#define PROCESS_BUILDER_HPP

#include <vector>
#include <string>
#include "../DataStructure.hpp"

class Process;

class ProcessBuilder{
public:
	ProcessBuilder(int (*func)(void*));
	ProcessBuilder(const std::vector<std::string>&);
	template<typename T,typename... Args>ProcessBuilder(T first,Args... args);

	Process* Start();

	std::vector<std::string> GetCommand() const{
		return m_com;
	}

	void SetCommand(const std::vector<std::string>& com){
		m_com = com;
	}

	std::string GetDirectory() const{
		return m_dir;
	}

	void SetDirectory(const std::string& dir){
		m_dir = dir;
	}

private:

	template<typename T,typename... Args>void _praseArgs(T,Args...);
	template<typename T>void _parseArgs(T);

	int m_forkType;
	int (*m_func)(void*);
	std::string m_dir;
	std::vector<std::string> m_com;	
};

#endif

