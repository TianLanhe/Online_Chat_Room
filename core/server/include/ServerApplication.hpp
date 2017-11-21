#ifndef SERVER_APPLICATION_HPP
#define SERVER_APPLICATION_HPP

#include "../../common/DataStructureBase.hpp"

class ServerApplication{
public:
	typedef size_type unsinged long;

public:
	~ServerApplication(){}

	virtual Status init() = 0;
	virtual Status term() = 0;

	virtual Status StartNetwork() = 0;

	virutal size_type GetMsgCount() = 0;
	virtual size_type GetFileCount() = 0;
	virtual size_type GetUserCount() = 0;
};

#endif

