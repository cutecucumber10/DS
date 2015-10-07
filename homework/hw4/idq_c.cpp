//File name : idq_c.cpp
//Purpose: implementation of idq.h

#include "idq_c.h"

#include <string>

IDQ_C::IDQ_C(std::string aID, int aNumber) {
	ID = aID;
	num = aNumber;
}

void IDQ_C::set_num(std::string a, int number) {
	if (a == "rent")
		num += number;
	else if (a == "return")
		num -= number;
}