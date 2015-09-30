//File: event.h
//Purpose: Header for declaration of events class and associated functions.

#ifndef event_h
#define event_h

#include <iostream>
#include <string>
#include <vector>

class Event {

	public:
		Event();
		Event(unsigned long long int Atimestamp, std::string Akiller, std::vector<std::string> assistant, std::string victim);
		//Accessors
		const unsigned long long int get_timestamp() const { return timestamp; }  // large int here
		const std::string& get_killer() const {return killer; }
		const std::vector<std::string>& get_assistant() const {return assistant; }   //assisstant is a vector because the number of assistant is unknown 
		const std::string& get_victim() const {return victim; }

		bool read(std::istream& in_str);   // a function to read events from file
		void print() const;

	private:
		//Representations
		unsigned long long int timestamp;
		std::string killer;
		std::vector<std::string> assistant;
		std::string victim;

};

#endif