//File name: event.cpp
//Purpose: implementation of event.h
//arthor: Xinyue Yan(yanx3)

#include "event.h"

#include <string>
#include <iostream>
#include <fstream>


bool Event::read(std::istream& in_str) {
	if (!(in_str >> c_id >> action >> timestamp >> num >> i_id >> name)) {
		return false;
	}
	return true;
}