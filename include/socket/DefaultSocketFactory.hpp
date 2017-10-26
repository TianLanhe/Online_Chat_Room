#ifndef DEFAULT_SOCKET_FACTORY_H
#define DEFAULT_SOCKET_FACTORY_H

class ClientSocket;
class ServerSocket;

class DefaultSocketFactory
{
public:
    ServerSocket* GetDefaultServerSocket();
    ClientSocket* GetDefaultClientSocket();
    static DefaultSocketFactory* GetInstance();

private:
	DefaultSocketFactory(){ }
	static DefaultSocketFactory* factory;
};

#endif
