#ifndef DEFAULT_SERVER_APPLICATION_HPP
#define DEFAULT_SERVER_APPLICATION_HPP

#include "include/ServerApplication.hpp"

class DefaultServerApplication : public ServerApplication{

public:
    DefaultServerApplication();
    ~DefaultServerApplication(){}

    Status init();
    Status term();

    size_type GetMsgCount(){
        _updateMsgCount();
        return m_msgCount;
    }

    size_type GetFileCount(){
        _updateFileCount();
        return m_fileCount;
    }

    size_type GetUserCount(){
        _updateUserCount();
        return m_fileCount;
    }

private:
    void _updateMsgCount();
    void _updateFileCount();
    void _updateUserCount();

private:
    size_type m_msgCount;
    size_type m_fileCount;
    size_type m_userCount;

    ClientsManager *m_manager;
    ConfigureReader *m_reader;

};

#endif

