//File name : idq_i.cpp
//Purpose: implementation of idq_i.h

#include "idq_i.h"

#include <string>

IDQ_I::IDQ_I(std::string aID, std::string aName, int aNumber) {
	ID = aID;
	name = aName;
	num = aNumber;
}

void IDQ_I::set_num(std::string a, int number) {
	if (a == "rent")
		num += number;
	else if (a == "return")
		num -= number;
}