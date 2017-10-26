#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
	virtual std::string getName() = 0;
	virtual std::string getId() = 0;
	virtual std::string getPwd() = 0;
	virtual bool checkPwd(const std::string&) = 0;
};

#endif