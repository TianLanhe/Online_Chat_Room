#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "Socket.hpp"

class ClientSocket;

class ServerSocket : public Socket
{
public:
	virtual Status bind(int) = 0;
	virtual bool isBind() = 0;
	virtual Status listen(int) = 0;
	virtual bool isListen() = 0;
	virtual Status accept(ClientSocket*&) = 0;
};

#endif