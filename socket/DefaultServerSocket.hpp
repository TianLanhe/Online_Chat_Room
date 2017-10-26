#ifndef DEFAULT_SERVER_SOCKET_H
#define DEFAULT_SERVER_SOCKET_H

#include "../include/socket/ServerSocket.hpp"

class ClientSocket;

class DefaultServerSocket : public ServerSocket
{
public:
	DefaultServerSocket():m_port(0), m_socket(0), m_bIsBind(false), m_bIsListen(false){ }
	explicit DefaultServerSocket(int socket);
	~DefaultServerSocket(){ if(m_socket) close(); }

	Status open();
	bool isOpen(){ return m_socket != 0; }
	Status close();
	Status read(int,std::string&);
	Status write(const char*);

	Status bind(int port);
	bool isBind(){ return m_bIsBind; }
	Status listen(int);
	bool isListen(){ return m_bIsListen; }
	Status accept(ClientSocket*&);

	int getPort(){ return m_port; }
	std::string getAddr() { return m_addr; }

private:
	std::string m_addr;
	int m_port;
	int m_socket;

	bool m_bIsBind;
	bool m_bIsListen;
};

#endif
