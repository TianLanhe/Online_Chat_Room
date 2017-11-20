#include "DefaultServerSocket.hpp"
#include "DefaultClientSocket.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

DefaultServerSocket::DefaultServerSocket(int socket)
{
	m_socket = socket;
	if(socket == 0){
		m_port = 0;
		m_bIsBind = false;
		m_bIsListen = false;
	}else{
		struct sockaddr_in ser_addr;
		socklen_t len = sizeof(ser_addr);

		getpeername(socket,(struct sockaddr*)&ser_addr,&len);

		// 默认该socket已经绑定到某一端口和地址，并已监听着
		m_addr = inet_ntoa(ser_addr.sin_addr);
		m_port = ntohl(ser_addr.sin_port);
		m_bIsBind = true;
		m_bIsListen = true;
	}
}

Status DefaultServerSocket::open()
{
	CHECK_ERROR(m_socket == 0);
	
	m_socket = socket(AF_INET,SOCK_STREAM,0);	//创建服务器套接字
	if(m_socket == -1){
		m_socket = 0;
		return ERROR;
	}else{
		m_port = 0;
		m_addr = "";
		return OK;
	}
}

Status DefaultServerSocket::close()
{
	CHECK_ERROR(m_socket != 0);

	int r = ::close(m_socket);
	m_socket = 0;
	m_port= 0;
	m_addr = "";
	m_bIsBind = false;
	m_bIsListen = false;
	return r == 0 ? OK : ERROR;
}

Status DefaultServerSocket::read(int read_byte, string& str)
{
	CHECK_ERROR(m_socket != 0 && !m_addr.empty() && m_port != 0);

	char content[read_byte + 1] = { 0 };
	int r = ::read(m_socket,content,sizeof(read_byte));
	if(r == -1)
		return ERROR;
	else{
		str = content;
		return OK;
	}
}

Status DefaultServerSocket::write(const char* content)
{
	CHECK_ERROR(m_socket != 0 && !m_addr.empty() && m_port != 0);

	int write_byte = ::write(m_socket,content,strlen(content));

	CHECK_ERROR(write_byte == strlen(content));
	return OK;
}

Status DefaultServerSocket::bind(int port)
{
	CHECK_ERROR(m_socket != 0 && !m_bIsBind);

	struct sockaddr_in server_addr;		  //服务器地址结构
	server_addr.sin_port = htons(port);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	CHECK_ERROR(::bind(m_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)) == 0);

	struct sockaddr_in ser_addr;
	socklen_t len = sizeof(ser_addr);
	getpeername(m_socket,(struct sockaddr*)&ser_addr,&len);

	m_port = port;
	m_addr = inet_ntoa(ser_addr.sin_addr);
	m_bIsBind = true;
	return OK;
}

Status DefaultServerSocket::listen(int num)
{
        CHECK_ERROR(!m_bIsListen);
	CHECK_ERROR(::listen(m_socket,num) == 0);	//设置最大监听数并监听

	m_bIsListen = true;
	return OK;
}

Status DefaultServerSocket::accept(ClientSocket* &socket)
{
	int client_socket = ::accept(m_socket,NULL,NULL);
	CHECK_ERROR(client_socket != -1);

	socket = new DefaultClientSocket(client_socket);
	return OK;
}
