#include "../include/process/ProcessBuilder.hpp"
#include "ProcessImpl.hpp"

Process* ProcessBuilder::Create(){
    switch (m_forkType) {
    case EXEC:
        if(m_com.empty())
            return nullptr;
        return GetProcessImpl(m_com);
    case INHERIT:
        if(m_func == nullptr)
            return nullptr;
        return GetProcessImpl(m_func);
    default:
        return nullptr;
    }
    return nullptr;
}

template<typename... Args>
void ProcessBuilder::_parseArgs(const std::string& first,Args... args){
    _parseArgs(first);
    _parseArgs(args...);
}

vector<string> ProcessBuilder::_splitCommand(const string& str){
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
