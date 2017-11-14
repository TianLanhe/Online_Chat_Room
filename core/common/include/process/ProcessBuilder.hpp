#ifndef PROCESS_BUILDER_HPP
#define PROCESS_BUILDER_HPP

#include <vector>
#include <string>

class Process;

enum TYPE{
    EXEC,
    INHERIT
};

class ProcessBuilder{
public:
        explicit ProcessBuilder(int (*func)(void*),void *arg = nullptr):m_forkType(INHERIT),m_func(func),m_arg(arg){}
        explicit ProcessBuilder(const std::vector<std::string>&):m_forkType(EXEC),m_func(nullptr),m_com(com),m_arg(nullptr){}
        explicit ProcessBuilder(const std::string&):m_forkType(EXEC),m_func(nullptr),m_arg(nullptr){
            m_com = _splitCommand(str);
        }
        template<typename... Args>
        ProcessBuilder(const std::string& first,Args... args):m_forkType(EXEC),m_func(nullptr),m_arg(nullptr){
            _praseArgs(first,args...);
        }

        Process* Create();

	std::vector<std::string> GetCommand() const{
		return m_com;
	}

	void SetCommand(const std::vector<std::string>& com){
		m_com = com;
        }

        void SetArg(void* arg){ m_arg = arg; }
        void* GetArg(){ return m_arg; }

private:

        template<typename... Args>void _parseArgs(const std::string&,Args...);
        void _parseArgs(const std::string& arg){
            m_com.push_back(arg);
        }

        std::vector<std::string> _splitCommand(const std::string&);

	int m_forkType;
        int (*m_func)(void*);
        std::vector<std::string> m_com;
        void* m_arg;
};

#endif

