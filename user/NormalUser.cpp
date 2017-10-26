#include "../include/User.hpp"

using namespace std;

class NormalUser : public User
{
public:
	NormalUser(const string& aId = "", const string& aName = "",
				const string& aPwd = ""):m_name(aName),m_id(aId),m_pwd(aPwd){}
	~NormalUser();

	string getId(){ return m_id; }
	string getName(){ return m_name; }
	string getPwd(){ return m_pwd; }
	bool checkPwd(const string& pwd){ return m_pwd == pwd; }

private:
	string m_name;
	string m_id;
	string m_pwd;
};
