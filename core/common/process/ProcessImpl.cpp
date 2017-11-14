#include "ProcessImpl.hpp"
#include <signal.h>

bool ProcessImpl::_hasTerminate(){
    if(!m_bTerminate && kill(m_pid,0) == -1 && errno == ERSCH)
        m_bTerminate = true;
    return m_bTerminate;
}

Status Start(){
    CHECK_ERROR(!_hasTerminate());
}

Status Terminate(){
    CHECK_ERROR(!_hasTerminate());
}

Status GetExitCode(int* retCode){
    CHECK_ERROR(!_hasTerminate());
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
    CHECK_ERROR(!m_hasWait);

    waitpid(m_pid,);
    m_hasWait = true;
    m_hTerminate = true;
    m_exitCode = code;
    return OK;
}

Process* GetProcessImpl(int (*)(void*)){

}

Process* GetProcessImpl(const std::vector<std::string>&){

}
