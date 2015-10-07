//File name: event.cpp
//Purpose: implementation of event.h

#include "event.h"

#include <string>
#include <iostream>
#include <fstream>


bool Event::read(std::istream& in_str) {
	if (!(in_str >> c_id >> action >> timestamp >> num >> i_id >> name)) {
		//std::cerr << "No more ids";
		return false;
	}
	//just print error and keep going without stopping
	//if (c_id[0] != 'C') {
	//	std::cerr << "Invalid customer information found for ID " << c_id <<\
	//	" in the customer file \n";
	//}
	return true;
}