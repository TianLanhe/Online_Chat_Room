#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "../DataStructureBase.hpp"

class Observer{
public:
	~Observer(){}
	
	virtual Status Update() = 0;
};

#endif

