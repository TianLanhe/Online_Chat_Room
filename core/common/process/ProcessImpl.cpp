#include "ProcessImpl.hpp"
#include <signal.h>
#include <errno.h>
#include <cstring>

using namespace std;

bool ProcessImpl::_hasTerminate(){
    if(!m_bTerminate && m_pid && kill(m_pid,0) == -1 && errno == ESRCH)
        m_bTerminate = true;
    return m_bTerminate;
}

ProcessImpl::ProcessImpl(const std::vector<std::string>& com):m_bHasWait(false),m_bTerminate(false),m_pid(0),m_exitCode(0),
    m_func(NULL),m_arg(NULL){
    m_com = com;
}

ProcessImpl::ProcessImpl(int (*func)(void*),void* arg):m_func(func),m_arg(arg),m_bHasWait(false),m_bTerminate(false),m_pid(0),m_exitCode(0){

}

ProcessImpl::~ProcessImpl(){
    if(m_pid){
        if(!_hasTerminate())
            Terminate();
        if(!m_bHasWait)
            WaitFor();
    }
}

Status ProcessImpl::Start(){
    CHECK_ERROR(!m_pid);

    m_pid = fork();
    if(!m_pid){
        if(m_func){
            m_func(m_arg);
            exit(0);
        }else{
            char **argvs = new char*[m_com.size()+1];
            for(vector<string>::size_type i=0;i<m_com.size();++i){
                argvs[i] = new char[m_com[i].size()+1];
                strcpy(argvs[i],m_com[i].c_str());
            }
            argvs[m_com.size()] = NULL;

            execvp(argvs[0],argvs);
        }
    }
    return OK;
}

Status ProcessImpl::Terminate(){
    CHECK_ERROR(m_pid && !_hasTerminate());
    CHECK_ERROR(kill(m_pid,SIGKILL) == 0);
    return OK;
}

Status ProcessImpl::GetExitCode(int* retCode){
    CHECK_ERROR(m_pid && _hasTerminate());
    CHECK_ERROR(retCode);

    BEFORE_CHECK_RESULT();
    if(!m_bHasWait){
        CHECK_RESULT(WaitFor());
        m_bHasWait = true;
    }

    *retCode = m_exitCode;
    return OK;
}

Status ProcessImpl::WaitFor(){
    CHECK_ERROR(m_pid && !m_bHasWait);

    int status;
    pid_t pid;
    pid = waitpid(m_pid,&status,0);
    CHECK_ERROR(pid == m_pid);

    m_bHasWait = true;
    m_bTerminate = true;

    int ret;
    if(WIFEXITED(status)){
        ret = WEXITSTATUS(status);
    }else if(WIFSIGNALED(status)){
        ret = WTERMSIG(status);
    }else{
        ret = -1;
    }
    m_exitCode = ret;
    return OK;
}

Process* GetProcessImpl(int (*func)(void*),void *arg){
    if(!func)
        return NULL;
    return new ProcessImpl(func,arg);
}

Process* GetProcessImpl(const vector<string>& command){
    if(command.size() < 1)
        return NULL;
    return new ProcessImpl(command);
}
