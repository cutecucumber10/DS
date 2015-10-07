//File name: customer.cpp
//Purpose: implement of customer.h

#include "customer.h"

#include <list>
#include <string>

//need when we initialize a customer....
Customer::Customer(std::string a_customer_id, std::string a_name) {
	c_id = a_customer_id;
	name = a_name;
}

//get a copy of rental list
void Customer::get_rental(std::list<IDQ_C>& a_rental) const {
	a_rental = rental;
}

//get a copy of pending list
void Customer::get_pending(std::list<IDQ_C>& a_pending) const {
	a_pending = pending;
}

//add to rental list, no amount, so no change....
void Customer::add_rental(IDQ_C an_action) {
	bool if_last_one = true;
	for (std::list<IDQ_C>::iterator p = rental.begin(); p != rental.end(); ++p) {
		if (an_action.get_i_id() < (*p).get_i_id()) {
			rental.insert(p, an_action);
			if_last_one = false;
			break;
		}
	}
	//corner case, it should be the last one....
	if (if_last_one == true) {
		rental.push_back(an_action);
	} 
}

//remove the specific rental element....
void Customer::erase_rental(int a) {
	//a list the location of the element in the list...
	//use int to find iterator....
	std::list<IDQ_C>::iterator p = rental.begin();
	for (int i = 0; i < a; ++i) {
		p++;
	}
	rental.erase(p);
}

void Customer::set_rental(int b, std::string a, int number) {
	//a may equal rent or return
	//b is the location of the rental element
	//int is the number needs to add/minus
	std::list<IDQ_C>::iterator p = rental.begin();
	for (int i = 0; i < b; ++i) {
		p++;
	}
	(*p).set_num(a,number);
}

void Customer::add_pending(IDQ_C an_action) {
	bool if_last_one = true;
	for (std::list<IDQ_C>::iterator p = pending.begin(); p != pending.end(); ++p) {
		if (an_action.get_i_id() < (*p).get_i_id()) {
			pending.insert(p, an_action);
			if_last_one = false;
			break;
		}
	}
	//corner case that the adding element should be the last one of the list....
	if (if_last_one == true) {
		pending.push_back(an_action);
	} 
}

void Customer::erase_pending(int a) {
	//int a is the location of the element in the list
	//find the iterator
	std::list<IDQ_C>::iterator p = pending.begin();
	for (int i = 0; i < a; ++i) {
		p++;
	}
	//add to rental list..
	rental.push_back(*p);
	//remove from pending list....
	pending.erase(p);
}

void Customer::set_pending(int a, int number) {
	//as new rule....pending maybe changed if the customer requested more than once
	//int a is the location of the element in the pending list
	//number is the number it needs to added.....
	//find the iterator first.....
	std::list<IDQ_C>::iterator p = pending.begin();
	for (int i = 0; i < a; i++) {
		p++;
	}
	(*p).set_num("rent",number);
}

void Customer::outputs(std::ostream& out_str) {
	out_str << c_id << " " << name << "\n";
	if (rental.size() != 0) {
		out_str << "Rentals: ";
		std::list<IDQ_C>::iterator a_rent;
		for (a_rent = rental.begin(); a_rent != rental.end(); ++a_rent) {
			out_str << (*a_rent).get_i_id() << " (" << ((*a_rent).get_num())\
			<<") " ;
		}
		out_str << "\n";
	}
	if (pending.size() != 0) {
		out_str << "Pending: " ;
		std::list<IDQ_C>::iterator a_pend;
		for (a_pend = pending.begin(); a_pend != pending.end(); ++a_pend) {
			out_str << (*a_pend).get_i_id() << " (" << (*a_pend).get_num()\
				<<") ";
		}
		out_str << "\n";
	}
	out_str << "\n";
}