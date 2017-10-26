#ifndef SOCKET_H
#define SOCKET_H

#include "../DataStructureBase.hpp"

#include <string>

class Socket
{
public:
	virtual ~Socket(){}

	virtual Status open() = 0;
	virtual bool isOpen() = 0;
	virtual Status close() = 0;
	virtual Status read(int,std::string&) = 0;
	virtual Status write(const std::string& str){ return write(str.c_str()); };
	virtual Status write(const char*) = 0;

	virtual int getPort() = 0;
	virtual std::string getAddr() = 0;
};

#endif