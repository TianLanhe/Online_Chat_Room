#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include "Socket.hpp"

class ClientSocket : public Socket
{
public:
	virtual Status connect(const std::string& addr, int port){ return connect(addr.c_str(),port); }
	virtual Status connect(const char*, int) = 0;
	virtual bool hasConnect() = 0;
};

#endif