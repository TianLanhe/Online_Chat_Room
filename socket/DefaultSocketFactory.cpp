#include "../include/socket/DefaultSocketFactory.hpp"
#include "DefaultServerSocket.hpp"
#include "DefaultClientSocket.hpp"

DefaultSocketFactory* DefaultSocketFactory::factory = NULL;

ServerSocket* DefaultSocketFactory::GetDefaultServerSocket(){
	return new DefaultServerSocket();
}

ClientSocket* DefaultSocketFactory::GetDefaultClientSocket(){
	return new DefaultClientSocket();
}

DefaultSocketFactory* DefaultSocketFactory::GetInstance(){
	if(!factory)
		factory = new DefaultSocketFactory();
	return factory;
}
