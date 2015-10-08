//File name : idq_i.cpp
//Purpose: implementation of idq_i.h
//arthor: Xinyue Yan(yanx3)

#include "idq_i.h"

#include <string>

//initializer
IDQ_I::IDQ_I(std::string aID, std::string aName, int aNumber) {
	ID = aID;
	name = aName;
	num = aNumber;
}

//use in item class change rental/pending
void IDQ_I::set_num(std::string a, int number) {
	if (a == "rent")
		num += number;
	else if (a == "return")
		num -= number;
}

//only use for popularity
void IDQ_I::outputs(std::ostream& out_str) {
	out_str << ID <<" "<< num <<" "<< name << "\n";
}