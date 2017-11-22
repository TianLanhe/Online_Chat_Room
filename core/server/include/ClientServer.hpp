#ifndef CLIENT_SERVER_HPP
#define CLIENT_SERVER_HPP

#include "../../common/include/DataStructureBase.hpp"

class ClientServer {
public:
	virtual Status UploadFile() = 0;
	virtual Status DownloadFile() = 0;

	virtual Status ReceiveMsg() = 0;
	virtual Status SendMsg() = 0;

	virtual Status Logout() = 0;
	virtual Status Login() = 0;

	virtual Status ChangePwd() = 0;

};

#endif

