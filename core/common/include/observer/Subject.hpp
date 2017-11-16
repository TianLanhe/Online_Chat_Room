#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "../DataStructureBase.hpp"

class Observer;

class Subject{
public:
	~Subject(){}

	virtual Status Regitster(const Observer*) = 0;
	virtual Status UnRegister(const Observer*) = 0;

	virtual Status Notify() = 0;
};

#endif

