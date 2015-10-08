//File name: event.h
//Purpose: store an event of rent or return of a customer at a 
//specific time (get a everything from file customer) 
//arthor: Xinyue Yan(yanx3)

#ifndef event_h
#define event_h

#include <string>

class Event {
	public:
		//Accesors
		const std::string& get_c_id() const {return c_id;}
		const std::string& get_action() const {return action;}
		const int get_num() const {return num;}
		const int get_timestamp() const {return timestamp;}
		const std::string& get_i_id() const {return i_id;}
		const std::string& get_name() const {return name;}

		//other member functions
		bool read(std::istream& in_str);

	private:
		std::string c_id;
		std::string action;
		int num;
		int timestamp;
		std::string i_id;
		std::string name;
};

#endif