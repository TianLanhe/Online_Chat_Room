#ifndef DEFAULT_CLIENT_SOCKET_H
#define DEFAULT_CLIENT_SOCKET_H

#include "../include/socket/ClientSocket.hpp"

class DefaultClientSocket : public ClientSocket
{
public:
	DefaultClientSocket():m_port(0), m_socket(0), m_bHasConnect(false){ }
    explicit DefaultClientSocket(int socket);
	~DefaultClientSocket(){ if(m_socket) close(); }

	Status open();
	bool isOpen(){ return m_socket != 0; }
	Status close();

	Status read(int,std::string&);
	Status write(const char*);

	Status connect(const char*,int);
	bool hasConnect(){ return m_bHasConnect; }

	int getPort(){ return m_port; }
	std::string getAddr() { return m_addr; }

private:
	int _getMaxTryTime(){ return 10; }

private:
	std::string m_addr;
	int m_port;
	int m_socket;

	bool m_bHasConnect;
};

#endif
