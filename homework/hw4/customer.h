//File customer.h
//Purpose: member type in the customer list, which will include 
//id, name, rental and pending lists
//arthor: Xinyue Yan(yanx3)

#ifndef customer_h
#define customer_h

#include "idq_c.h"

#include <string>
#include <list>
#include <iostream>
#include <fstream>

class Customer {
	public:
		Customer(std::string a_customer_id, std::string a_name);

		//Accessors
		const std::string& get_c_id() const {return c_id;}
		const std::string& get_name() const {return name;}
		void get_rental(std::list<IDQ_C>& a_rental) const;
		void get_pending(std::list<IDQ_C>& a_pending) const;

		//Modifiers
		void add_rental(IDQ_C an_action);
		void erase_rental(int a);
		void set_rental(int b, std::string a, int number);
		void add_pending(IDQ_C an_action);
		void erase_pending(int a);
		void set_pending(int a, int number);

		//othermember function
		void outputs(std::ostream& out_str);

	private:
		std::string c_id;
		std::string name;
		std::list<IDQ_C> rental;
		std::list<IDQ_C> pending;
};

#endif