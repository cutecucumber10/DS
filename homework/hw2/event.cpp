//File: event.h
//Purpose: Implementation of the class Event

#include <iostream>
#include <string>
#include "event.h"

Event::Event() {  //default values
	timestamp = 0;
	killer = "";
	assistant.clear();
	victim = "";
}

void Event::print() const {
	std::cout << timestamp << " killer: " << killer << " victim: " << victim << " assistant ";
	for (unsigned int i = 0; i < assistant.size(); ++i) {
		std::cout << assistant[i]<<" ";
	}
	std::cout  <<std::endl;

}

bool Event::read(std::istream& in_str) {
	std::string trash;   //those data which not needed for calculating/making tables
	in_str >> trash;  //fisrt string/char is @
	//"End", finish the read function
	assistant.clear();
	if (trash=="END") {
		return false;
	}
	else {
		in_str >> timestamp; //second one is timestamp
		in_str >> killer; // third one is killer
		in_str >> trash; //fourth may be "[" or "killed"
		if (trash[0] == '[') {   //'['  //use trash as a temporary variable to represent assistant, if trash is meaning, push back to assistant, vice versa.
			while (trash[0] != ']') {
				in_str >> trash;
				assistant.push_back(trash);
			}
			assistant.pop_back();
			in_str >> trash;  //"killed" string means nothing
			in_str >> victim;
		}
		else { //"killed"
			in_str >> victim;
		}
	return true;  //everything is fine
	}
}