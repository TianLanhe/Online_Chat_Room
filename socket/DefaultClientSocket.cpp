#include "DefaultClientSocket.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

DefaultClientSocket::DefaultClientSocket(int socket)
{
	m_socket = socket;
	if(socket == 0){
		m_port = 0;
		m_bHasConnect = false;
	}else{
		struct sockaddr_in cli_addr;
		socklen_t len = sizeof(cli_addr);

		getpeername(socket,(struct sockaddr*)&cli_addr,&len);

		// 默认该socket已经绑定到某一端口和地址，并已与服务器socket链接
		m_addr = inet_ntoa(cli_addr.sin_addr);
		m_port = ntohs(cli_addr.sin_port);
		m_bHasConnect = true;
	}
}

Status DefaultClientSocket::open()
{
	CHECK_ERROR(m_socket == 0);
	
	m_socket = socket(AF_INET,SOCK_STREAM,0);	//创建客户端套接字
	if(m_socket == -1){
		m_socket = 0;
		return ERROR;
	}else{
		m_port = 0;
		m_addr = "";
		return OK;
	}
}

Status DefaultClientSocket::close()
{
	CHECK_ERROR(m_socket != 0);

	int r = ::close(m_socket);
	m_socket = 0;
	m_port = 0;
	m_addr = "";
	m_bHasConnect = false;
	return r == 0 ? OK : ERROR;
}

Status DefaultClientSocket::connect(const char* addr, int port)
{
	CHECK_ERROR(m_socket != 0 && !m_bHasConnect);

	struct sockaddr_in server_addr;
	server_addr.sin_addr.s_addr = inet_addr(addr);
	server_addr.sin_port = htons(port);
	server_addr.sin_family = AF_INET;

	int try_time = 0;			//如果不成功每隔一秒连接一次，最多10次
	while(try_time++ < _getMaxTryTime() && ::connect(m_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)) == -1)
		sleep(1);

	if(try_time == 10)
		return ERROR;
	else{
		struct sockaddr_in cli_addr;
		socklen_t len=sizeof(cli_addr);
		getpeername(m_socket,(struct sockaddr*)&cli_addr,&len);

		m_addr = inet_ntoa(cli_addr.sin_addr);
		m_port = ntohl(cli_addr.sin_port);
		m_bHasConnect = true;

		CHECK_ERROR(m_port != 0 && m_addr != "");
		return OK;
	}
}

Status DefaultClientSocket::read(int read_byte, string& str)
{
	CHECK_ERROR(m_socket != 0 && m_bHasConnect);

	char content[read_byte + 1] = { 0 };
	int r = ::read(m_socket,content,sizeof(read_byte));
	if(r == -1)
		return ERROR;
	else{
		str = content;
		return OK;
	}
}

Status DefaultClientSocket::write(const char* content)
{
	CHECK_ERROR(m_socket != 0 && m_bHasConnect);

	int write_byte = ::write(m_socket,content,strlen(content));

	CHECK_ERROR(write_byte == strlen(content));
	return OK;
}
