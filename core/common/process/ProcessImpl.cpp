#include "ProcessImpl.hpp"
#include <signal.h>

bool ProcessImpl::_hasTerminate(){
    if(!m_bTerminate && m_pid && kill(m_pid,0) == -1 && errno == ERSCH)
        m_bTerminate = true;
    return m_bTerminate;
}

vector<string> ProcessImpl::_splitCommand(const string& str){
    vector<string> vec;

    string::size_type start = str.find_first_not_of(" \t\n",0);
    string::size_type end;
    while(start != string::npos){
        end = str.find_first_of(" \t\n",start);
        vec.push_back(string(str.begin()+start,str.begin()+end));
        start = str.find_first_not_of(" \t\n",end);
    }
    return vec;
}

ProcessImpl::ProcessImpl(const std::string& com):m_bHasWait(false),m_bTerminate(false),m_pid(0),m_exitCode(0),
    m_func(NULL),m_arg(NULL){
    m_com = _splitCommand(com);
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

Status Start(){
    CHECK_ERROR(!m_pid);

    m_pid = fork();
    if(!m_pid){
        m_func(arg);
        exit(0);
    }else{
        return OK;
    }
}

Status Terminate(){
    CHECK_ERROR(m_pid && !_hasTerminate());
    CHECK_ERROR(kill(m_pid,SIGKILL) == 0);
    return OK;
}

Status GetExitCode(int* retCode){
    CHECK_ERROR(m_pid && _hasTerminate());
    CHECK_ERROR(retCode);

    BEFORE_CHECK_RESULT();
    if(!m_hasWait){
        CHECK_RESULT(Wait());
        m_hasWait = true;
    }

    *retCode = m_exitCode;
    return OK;
}

Status ProcessImpl::WaitFor(){
    CHECK_ERROR(m_pid && !m_bHasWait);

    int status;
    pid_t pid;
    pid = waitpid(m_pid,&status,NULL);
    CHECK_ERROR(ret == m_pid);

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
